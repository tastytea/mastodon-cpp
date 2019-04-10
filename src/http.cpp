/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <functional>   // std::bind
#include <list>
#include <cstring>      // std::strncmp
#include <exception>
#include <thread>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include "debug.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;
namespace curlopts = curlpp::options;
using std::cerr;

API::http::http(const API &api, const string &instance,
                const string &access_token)
: parent(api)
, _instance(instance)
, _access_token(access_token)
, _cancel_stream(false)
{
    curlpp::initialize();
}

API::http::~http()
{
    curlpp::terminate();
}

return_call API::http::request(const http_method &meth, const string &path)
{
    return request(meth, path, curlpp::Forms());
}

return_call API::http::request(const http_method &meth, const string &path,
                               const curlpp::Forms &formdata)
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
            ret = request_common(http_method::GET_STREAM, path,
                                 curlpp::Forms(), stream);
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
                                      const curlpp::Forms &formdata,
                                      string &answer)
{
    using namespace std::placeholders;  // _1, _2, _3

    ttdebug << "Path is: " << path << '\n';

    try
    {
        curlpp::Easy request;
        std::list<string> headers;

        request.setOpt<curlopts::Url>("https://" + _instance + path);
        ttdebug << "User-Agent: " << parent.get_useragent() << "\n";
        request.setOpt<curlopts::UserAgent>(parent.get_useragent());

        {
            string proxy;
            string userpw;
            parent.get_proxy(proxy, userpw);
            if (!proxy.empty())
            {
                request.setOpt<curlopts::Proxy>(proxy);
                if (!userpw.empty())
                {
                    request.setOpt<curlopts::ProxyUserPwd>(userpw);
                }
            }
        }

        if (!_access_token.empty())
        {
            headers.push_back("Authorization: Bearer " + _access_token);
        }
        if (meth != http_method::GET_STREAM)
        {
            headers.push_back("Connection: close");
            // Get headers from server
            request.setOpt<curlpp::options::Header>(true);
        }

        request.setOpt<curlopts::HttpHeader>(headers);
        request.setOpt<curlopts::FollowLocation>(true);
        request.setOpt<curlopts::WriteFunction>
            (std::bind(&http::callback_write, this, _1, _2, _3, &answer));
        request.setOpt<curlopts::ProgressFunction>
            (std::bind(&http::callback_progress, this, _1, _2, _3, _4));
        request.setOpt<curlopts::NoProgress>(0);
        if (!formdata.empty())
        {
            request.setOpt<curlopts::HttpPost>(formdata);
        }

        switch (meth)
        {
        case http_method::GET:
        case http_method::GET_STREAM:
            break;
        case http_method::PATCH:
            request.setOpt<curlopts::CustomRequest>("PATCH");
            break;
        case http_method::POST:
            request.setOpt<curlopts::CustomRequest>("POST");
            break;
        case http_method::PUT:
            request.setOpt<curlopts::CustomRequest>("PUT");
            break;
        case http_method::DELETE:
            request.setOpt<curlopts::CustomRequest>("DELETE");
            break;
        }

        //request.setOpt<curlopts::Verbose>(true);

        answer.clear();
        request.perform();
        uint16_t http_code = curlpp::infos::ResponseCode::get(request);
        ttdebug << "Response code: " << http_code << '\n';
        // Work around "HTTP/1.1 100 Continue\r\n\r\nHTTP/1.1 200 OK"
        size_t pos = answer.find("\r\n\r\n", 25);
        _headers = answer.substr(0, pos);
        // Only return body
        answer = answer.substr(pos + 4);

        if (http_code == 200 || http_code == 302 || http_code == 307)
        {   // OK or Found or Temporary Redirect
            return { 0, "", http_code, answer };
        }
        else if (http_code == 301 || http_code == 308)
        {   // Moved Permanently or Permanent Redirect
            // return new URL
            answer = curlpp::infos::EffectiveUrl::get(request);
            return { 78, "Remote address changed", http_code, answer };
        }
        else if (http_code == 0)
        {
            return { 255, "Unknown error", http_code, answer };
        }
        else
        {
            return { 111, "Connection refused", http_code, answer };
        }
    }
    catch (curlpp::RuntimeError &e)
    {
        const string what = e.what();
        // This error is thrown if http.cancel_stream() is used.
        if ((what.compare(0, 16, "Callback aborted") == 0) ||
            (what.compare(0, 19, "Failed writing body") == 0))
        {
            ttdebug << "Request was cancelled by user\n";
            return { 0, "Request was cancelled by user", 0, "" };
        }
        else if (what.compare(what.size() - 20, 20, "Connection timed out") == 0)
        {
            ttdebug << what << "\n";
            return { 110, "Connection timed out", 0, "" };
        }
        else if (what.compare(0, 23, "Could not resolve host:") == 0)
        {
            ttdebug << what << "\n";
            return { 113, "Could not resolve host", 0, "" };
        }

        if (parent.exceptions())
        {
            std::rethrow_exception(std::current_exception());
        }
        else
        {
            ttdebug << "curlpp::RuntimeError: " << e.what() << std::endl;
            return { 192, e.what(), 0, "" };
        }
    }
    catch (curlpp::LogicError &e)
    {
        if (parent.exceptions())
        {
            std::rethrow_exception(std::current_exception());
        }

        ttdebug << "curlpp::LogicError: " << e.what() << std::endl;
        return { 193, e.what(), 0, "" };
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
