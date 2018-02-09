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
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
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
{
    curlpp::initialize();
}

const std::uint16_t API::http::request_sync(const method &meth,
                                            const string &path,
                                            string &answer)
{
    return request_sync(meth, path, curlpp::Forms(), answer);
}

const std::uint16_t API::http::request_sync(const method &meth,
                                            const string &path,
                                            const curlpp::Forms &formdata,
                                            string &answer)
{
    ttdebug << "Path is: " << path << '\n';
    
    try
    {
        std::ostringstream oss;
        curlpp::Easy request;
        request.setOpt<curlopts::Url>("https://" + _instance + path);
        request.setOpt<curlopts::UserAgent>(parent.get_useragent());
        request.setOpt<curlopts::HttpHeader>(
        {
            "Connection: close",
            "Authorization: Bearer " + _access_token
        });
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
        
        oss << request;
        answer = oss.str();
    }
    catch (curlpp::RuntimeError &e)
    {
        cerr << "RUNTIME ERROR: " << e.what() << std::endl;
        return 0xffff;
    }
    catch (curlpp::LogicError &e)
    {
        cerr << "LOGIC ERROR: " << e.what() << std::endl;
        return 0xffff;
    }

    return 0;
}
