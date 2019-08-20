/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <functional>   // std::bind
#include <exception>
#include <thread>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <Poco/Environment.h>
#include <Poco/Exception.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SSLException.h>
#include "debug.hpp"
#include "mastodon-cpp.hpp"
#include <string>

using namespace Mastodon;
namespace curlopts = curlpp::options;
using std::cerr;
using std::istream;
using std::make_unique;
using std::move;
using Poco::Net::HTTPSClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Environment;

API::http::http(const API &api, const string &instance,
                const string &access_token)
: parent(api)
, _instance(instance)
, _access_token(access_token)
, _cancel_stream(false)
{
    curlpp::initialize();

    Poco::Net::initializeSSL();

    // FIXME: rewrite set_proxy() and set proxy here.
    // string proxy_host, proxy_userpw;
    // parent.get_proxy(proxy_host, proxy_userpw);

    try
    {
        HTTPSClientSession::ProxyConfig proxy;
        string proxy_env = Environment::get("http_proxy");
        size_t pos;

        // Only keep text between // and /.
        if ((pos = proxy_env.find("//")) != string::npos)
        {
            proxy_env = proxy_env.substr(pos + 2);
        }
        if ((pos = proxy_env.find('/')) != string::npos)
        {
            proxy_env = proxy_env.substr(0, pos);
        }

        if ((pos = proxy_env.find(':')) != string::npos)
        {
            proxy.host = proxy_env.substr(0, pos);
            proxy.port = std::stoi(proxy_env.substr(pos + 1));
        }
        else
        {
            proxy.host = proxy_env;
        }

        HTTPSClientSession::setGlobalProxyConfig(proxy);
    }
    catch (const std::exception &)
    {
        // No proxy found, no problem.
    }

}

API::http::~http()
{
    curlpp::terminate();

    Poco::Net::uninitializeSSL();
}

return_call API::http::request(const http_method &meth, const string &path)
{
    return request(meth, path, make_unique<HTMLForm>());
}

return_call API::http::request(const http_method &meth, const string &path,
                               unique_ptr<HTMLForm> formdata)
{
    string answer;
    return request_common(meth, path, move(formdata), answer);
}

void API::http::request_stream(const string &path, string &stream)
{
    static return_call ret;
    _streamthread = std::thread(
        [&, path]               // path is captured by value because it may be
        {                       // deleted before we access it.
            ret = request_common(http_method::GET_STREAM, path,
                                 make_unique<HTMLForm>(), stream);
            ttdebug << "Remaining content of the stream: " << stream << '\n';
            if (!ret)
            {
                // Embed the HTTP status code in stream on error.
                stream += "event: ERROR\ndata: {\"error_code\":"
                    + std::to_string(ret.error_code) +  ",\"http_error\":"
                    + std::to_string(ret.http_error_code) + "}\n";
            }
        });
}

return_call API::http::request_common(const http_method &meth,
                                      const string &path,
                                      unique_ptr<HTMLForm> formdata,
                                      string &answer)
{
    ttdebug << "Path is: " << path << '\n';

    try
    {
        string method;

        // TODO: operator string on http_method?
        switch (meth)
        {
        case http_method::GET:
        case http_method::GET_STREAM:
        {
            method = HTTPRequest::HTTP_GET;
            break;
        }
        case http_method::PUT:
        {
            method = HTTPRequest::HTTP_PUT;
            break;
        }
        case http_method::POST:
        {
            method = HTTPRequest::HTTP_POST;
            break;
        }
        case http_method::PATCH:
        {
            method = HTTPRequest::HTTP_PATCH;
            break;
        }
        case http_method::DELETE:
        {
            method = HTTPRequest::HTTP_DELETE;
            break;
        }
        default:
        {
            break;
        }
        }

        HTTPSClientSession session(_instance);
        HTTPRequest request(method, path, HTTPMessage::HTTP_1_1);
        request.set("User-Agent", parent.get_useragent());

        if (!_access_token.empty())
        {
            request.set("Authorization", " Bearer " + _access_token);
        }

        if (!formdata->empty())
        {
            // TODO: Test form submit.
            // TODO: Change maptoformdata() and so on.
            formdata->prepareSubmit(request);
        }

        HTTPResponse response;

        session.sendRequest(request);
        istream &rs = session.receiveResponse(response);

        const uint16_t http_code = response.getStatus();
        ttdebug << "Response code: " << http_code << '\n';

        answer.clear();
        StreamCopier::copyToString(rs, answer);

        switch (http_code)
        {
        case HTTPResponse::HTTP_OK:
        {
            return { 0, "", http_code, answer };
        }
        // Not using the constants because some are too new for Debian stretch.
        case 301:               // HTTPResponse::HTTP_MOVED_PERMANENTLY
        case 308:               // HTTPResponse::HTTP_PERMANENT_REDIRECT
        case 302:               // HTTPResponse::HTTP_FOUND
        case 303:               // HTTPResponse::HTTP_SEE_OTHER
        case 307:               // HTTPResponse::HTTP_TEMPORARY_REDIRECT
        {
            string location = response.get("Location");

            // TODO: Test this.
            if (location.substr(0, 4) == "http")
            {                   // Remove protocol and instance from path.
                size_t pos1 = location.find("//") + 2;
                size_t pos2 = location.find('/', pos1);

                if (location.substr(pos1, pos2) != _instance)
                {               // Return new location if the domain changed.
                    return { 78, "Remote address changed", http_code,
                             location };
                }

                location = location.substr(pos2);
            }

            if (http_code == 301 || http_code == 308)
            {                   // Return new location for permanent redirects.
                return { 78, "Remote address changed", http_code, location };
            }
            else
            {
                return request_common(meth, location, move(formdata), answer);
            }
        }
        default:
        {
            return { 111, "Connection refused", http_code, answer };
        }
        }
    }
    catch (const Poco::Net::DNSException &e)
    {
        if (parent.exceptions())
        {
            e.rethrow();
        }

        ttdebug << e.displayText() << "\n";
        return { 113, e.displayText(), 0, "" };
    }
    catch (const Poco::Net::ConnectionRefusedException &e)
    {
        if (parent.exceptions())
        {
            e.rethrow();
        }

        ttdebug << e.displayText() << "\n";
        return { 111, e.displayText(), 0, "" };
    }
    catch (const Poco::Net::SSLException &e)
    {
        if (parent.exceptions())
        {
            e.rethrow();
        }

        ttdebug << e.displayText() << "\n";
        return { 150, e.displayText(), 0, "" };
    }
    catch (const Poco::Net::NetException &e)
    {
        if (parent.exceptions())
        {
            e.rethrow();
        }

        ttdebug << "Unknown network error: " << e.displayText() << std::endl;
        return { 255, e.displayText(), 0, "" };
    }
    catch (const std::exception &e)
    {
        if (parent.exceptions())
        {
            std::rethrow_exception(std::current_exception());
        }

        ttdebug << "Unknown error: " << e.what() << std::endl;
        return { 255, e.what(), 0, "" };
    }
}

void API::http::get_headers(string &headers) const
{
    headers = _headers;
}

size_t API::http::callback_write(char* data, size_t size, size_t nmemb,
                                 string *str)
{
    std::lock_guard<std::mutex> lock(_mutex);
    str->append(data, size * nmemb);
    // ttdebug << "Received " << size * nmemb << " Bytes\n";
    return size * nmemb;
}

double API::http::callback_progress(double /* dltotal */, double /* dlnow */,
                                    double /* ultotal */, double /* ulnow */)
{
    if (_cancel_stream)
    {
        // This throws the runtime error: Callback aborted
        return 1;
    }
    return 0;
}

void API::http::cancel_stream()
{
    _cancel_stream = true;
    _streamthread.join();
}

std::mutex &API::http::get_mutex()
{
    return _mutex;
}
