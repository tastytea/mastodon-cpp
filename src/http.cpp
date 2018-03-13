/*  This file is part of mastodon-cpp.
 *  Copyright © 2018 tastytea <tastytea@tastytea.de>
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

#include <string>
#include <cstdint>
#include <iostream>
#include <functional>   // std::bind
#include <list>
#include <cstring>      // std::strncmp
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include "macros.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;
namespace curlopts = curlpp::options;
using std::string;
using std::cerr;

API::http::http(const API &api, const string &instance,
                const string &access_token)
: parent(api)
, _instance(instance)
, _access_token(access_token)
, _abort_stream(false)
{
    curlpp::initialize();
}

API::http::~http()
{
    curlpp::terminate();
}

const std::uint16_t API::http::request(const method &meth,
                                       const string &path,
                                       string &answer)
{
    return request(meth, path, curlpp::Forms(), answer);
}

const std::uint16_t API::http::request(const method &meth,
                                       const string &path,
                                       const curlpp::Forms &formdata,
                                       string &answer)
{
    using namespace std::placeholders;  // _1, _2, _3

    std::uint16_t ret = 0;
    ttdebug << "Path is: " << path << '\n';
    
    try
    {
        curlpp::Easy request;
        std::list<string> headers;

        request.setOpt<curlopts::Url>("https://" + _instance + path);
        ttdebug << "User-Agent: " << parent.get_useragent() << "\n";
        request.setOpt<curlopts::UserAgent>(parent.get_useragent());

        headers.push_back("Connection: close");
        if (!_access_token.empty())
        {
            headers.push_back("Authorization: Bearer " + _access_token);
        }
        request.setOpt<curlopts::HttpHeader>(headers);

        // Get headers from server
        if (meth != http::method::GET_STREAM)
        {
            request.setOpt<curlpp::options::Header>(true);
        }
        request.setOpt<curlopts::FollowLocation>(true);
        request.setOpt<curlpp::options::WriteFunction>
            (std::bind(&http::callback, this, _1, _2, _3, &answer));
        if (!formdata.empty())
        {
            request.setOpt<curlopts::HttpPost>(formdata);
        }

        switch (meth)
        {
            case http::method::GET:
                break;
            case http::method::PATCH:
                request.setOpt<curlopts::CustomRequest>("PATCH");
                break;
            case http::method::POST:
                request.setOpt<curlopts::CustomRequest>("POST");
                break;
            case http::method::PUT:
                request.setOpt<curlopts::CustomRequest>("PUT");
            case http::method::DELETE:
                request.setOpt<curlopts::CustomRequest>("DELETE");
            default:
                break;
        }
        
        //request.setOpt<curlopts::Verbose>(true);

        answer.clear();
        request.perform();
        ret = curlpp::infos::ResponseCode::get(request);
        ttdebug << "Response code: " << ret << '\n';
        // Work around "HTTP/1.1 100 Continue\r\n\r\nHTTP/1.1 200 OK"
        size_t pos = answer.find("\r\n\r\n", 25);
        _headers = answer.substr(0, pos);

        if (ret == 200 || ret == 302 || ret == 307)
        {   // OK or Found or Temporary Redirect
            // Only return body
            answer = answer.substr(pos + 4);
            return 0;
        }
        else if (ret == 301 || ret == 308)
        {   // Moved Permanently or Permanent Redirect
            // return new URL
            answer = curlpp::infos::EffectiveUrl::get(request);
            return 13;
        }
        else
        {
            return ret;
        }
    }
    catch (curlpp::RuntimeError &e)
    {
        if (std::strncmp(e.what(),
                         "Failed writing body", 19) == 0)
        {
            ttdebug << "Request was aborted by user\n";
            return 14;
        }
        else if (std::strncmp(e.what(),
                              "Failed to connect to", 20) == 0)
        {
            ret = 20;
        }
        else if (std::strncmp(e.what(),
                              "Couldn't resolve host", 21) == 0 ||
                 std::strncmp(e.what(),
                              "Could not resolve host", 22) == 0)
        {
            ret = 21;
        }
        else if (std::strncmp(e.what(),
                              "Network is unreachable", 22) == 0)
        {
            ret = 22;
        }
        else
        {
            cerr << "RUNTIME ERROR: " << e.what() << std::endl;
            ret = 0xffff;
        }
        ttdebug << e.what() << std::endl;
        
        return ret;
    }
    catch (curlpp::LogicError &e)
    {
        cerr << "LOGIC ERROR: " << e.what() << std::endl;
        return 0xffff;
    }

    return ret;
}

const void API::http::get_headers(string &headers) const
{
    headers = _headers;
}

const size_t API::http::callback(char* data, size_t size, size_t nmemb,
                                 string *str)
{
    if (_abort_stream)
    {
        // This throws the runtime error: Failed writing body
        return 0;
    }
    str->append(data, size * nmemb);
    // ttdebug << "Received " << size * nmemb << " Bytes\n";
    return size * nmemb;
};

const void API::http::abort_stream()
{
    _abort_stream = true;
}
