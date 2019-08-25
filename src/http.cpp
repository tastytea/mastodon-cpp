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
#include <regex>
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

using namespace Mastodon;
using std::cerr;
using std::istream;
using std::make_unique;
using std::move;
using std::regex;
using std::regex_search;
using std::smatch;
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
    Poco::Net::initializeSSL();

    // FIXME: rewrite set_proxy() that it calls set_proxy() here.

    try
    {
        string env_proxy = Environment::get("http_proxy");
        size_t pos;

        // Only keep text between // and /.
        if ((pos = env_proxy.find("//")) != string::npos)
        {
            env_proxy = env_proxy.substr(pos + 2);
        }
        if ((pos = env_proxy.find('/')) != string::npos)
        {
            env_proxy = env_proxy.substr(0, pos);
        }

        if ((pos = env_proxy.find('@')) != string::npos)
        {
            string hostport = env_proxy.substr(pos + 1);
            string userpw = env_proxy.substr(0, pos);
            parent.set_proxy(hostport, userpw);
        }
        else
        {
            parent.set_proxy(env_proxy);
        }
    }
    catch (const std::exception &)
    {
        // No proxy found, no problem.
    }

}

API::http::~http()
{
    Poco::Net::uninitializeSSL();
}

void API::http::set_proxy(const string &hostport, const string &userpw)
{
    // TODO: Test proxy.

    try
    {
        HTTPSClientSession::ProxyConfig proxyconfig;
        size_t pos = hostport.find(':');

        proxyconfig.host = hostport.substr(0, pos);
        if (pos != string::npos)
        {
            proxyconfig.port = std::stoi(hostport.substr(pos + 1));
        }

        if (!userpw.empty())
        {
            pos = userpw.find(':');
            proxyconfig.username = userpw.substr(0, pos);
            if (pos != string::npos)
            {
                proxyconfig.password = userpw.substr(pos + 1);
            }
        }

        HTTPSClientSession::setGlobalProxyConfig(proxyconfig);
    }
    catch (const std::exception &e)
    {
        if (parent.exceptions())
        {
            std::rethrow_exception(std::current_exception());
        }
    }
}

return_call API::http::request(const http_method &meth, const string &path)
{
    HTMLForm form;
    return request(meth, path, form);
}

return_call API::http::request(const http_method &meth, const string &path,
                               HTMLForm &formdata)
{
    string answer;
    return request_common(meth, path, formdata, answer);
}

void API::http::request_stream(const string &path, string &stream)
{
    static return_call ret;
    _streamthread = std::thread(
        [&, path]               // path is captured by value because it may be
        {                       // deleted before we access it.
            HTMLForm form;
            ret = request_common(http_method::GET_STREAM, path,
                                 form, stream);
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
                                      HTMLForm &formdata,
                                      string &answer)
{
    ttdebug << "Path is: " << path << '\n';

    try
    {
        string method;

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

        if (!formdata.empty())
        {
            ttdebug << "Size of HTMLForm is " << formdata.size() << '\n';
            formdata.prepareSubmit(request);
            formdata.write(session.sendRequest(request));
        }
        else
        {
            session.sendRequest(request);
        }

        HTTPResponse response;
        istream &rs = session.receiveResponse(response);

        const uint16_t http_code = response.getStatus();
        ttdebug << "Response code: " << http_code << '\n';

        answer.clear();
        StreamCopier::copyToString(rs, answer);

        switch (http_code)
        {
        case HTTPResponse::HTTP_OK:
        {
            return { error::OK, "", http_code, answer };
        }
        // Not using the constants because some are too new for Debian stretch.
        case 301:               // HTTPResponse::HTTP_MOVED_PERMANENTLY
        case 308:               // HTTPResponse::HTTP_PERMANENT_REDIRECT
        case 302:               // HTTPResponse::HTTP_FOUND
        case 303:               // HTTPResponse::HTTP_SEE_OTHER
        case 307:               // HTTPResponse::HTTP_TEMPORARY_REDIRECT
        {
            ttdebug << "HTTP redirect.\n";
            string location = response.get("Location");

            if (location.substr(0, 4) == "http")
            {                   // Remove protocol and instance from path.
                size_t pos1 = location.find("//") + 2;
                size_t pos2 = location.find('/', pos1);

                if (location.substr(pos1, pos2 - pos1) != _instance)
                {               // Return new location if the domain changed.
                    ttdebug << "New location is on another domain.\n";
                    return { error::URL_CHANGED, "Remote address changed",
                             http_code, location };
                }

                location = location.substr(pos2);
            }

            if (http_code == 301 || http_code == 308)
            {                   // Return new location for permanent redirects.
                return { error::URL_CHANGED, "Remote address changed",
                         http_code, location };
            }
            else
            {
                ttdebug << "Following temporary redirect: " << location << '\n';
                return request_common(meth, location, formdata, answer);
            }
        }
        default:
        {
            return { error::CONNECTION_REFUSED, "Connection refused",
                     http_code, answer };
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
        return { error::DNS, e.displayText(), 0, "" };
    }
    catch (const Poco::Net::ConnectionRefusedException &e)
    {
        if (parent.exceptions())
        {
            e.rethrow();
        }

        ttdebug << e.displayText() << "\n";
        return { error::CONNECTION_REFUSED, e.displayText(), 0, "" };
    }
    catch (const Poco::Net::SSLException &e)
    {
        if (parent.exceptions())
        {
            e.rethrow();
        }

        ttdebug << e.displayText() << "\n";
        return { error::ENCRYPTION, e.displayText(), 0, "" };
    }
    catch (const Poco::Net::NetException &e)
    {
        if (parent.exceptions())
        {
            e.rethrow();
        }

        ttdebug << "Unknown network error: " << e.displayText() << std::endl;
        return { error::UNKNOWN, e.displayText(), 0, "" };
    }
    catch (const std::exception &e)
    {
        if (parent.exceptions())
        {
            std::rethrow_exception(std::current_exception());
        }

        ttdebug << "Unknown error: " << e.what() << std::endl;
        return { error::UNKNOWN, e.what(), 0, "" };
    }
}

// FIXME: get_headers() doesn't work anymore.
void API::http::get_headers(string &headers) const
{
    headers = _headers;
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
