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
#include <map>
#include <vector>
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include "version.hpp"
#include "macros.hpp"
#include "mastodon-cpp.hpp"

#include <iostream>

using namespace Mastodon;
using std::string;

API::API(const string &instance, const string &access_token)
: _instance(instance)
, _access_token(access_token)
, _useragent(string("mastodon-cpp/") + global::version)
, _http(*this, instance, access_token)
{
    //
}

const void API::set_useragent(const std::string &useragent)
{
    _useragent = useragent;
}

const string API::get_useragent() const
{
    return _useragent;
}

const std::string API::urlencode(const string &str) const
{
    std::ostringstream oss;

    for (const std::uint8_t &b: str)
    {
        // Check for unreserved characters (RFC 3986 section 2.3)
        if ((b >= 0x30 && b <= 0x39) || // 0-9
            (b >= 0x41 && b <= 0x5A) || // A-Z
            (b >= 0x61 && b <= 0x7A) || // a-z
            b == 0x2D || b == 0x2E ||   // -, .
            b == 0x5F || b == 0x7E)     // _, ~
        {
            oss << b;
        }
        else
        {
            oss << '%' << std::hex << std::uppercase << (int)(unsigned char)b;
        }
    }

    return oss.str();
}

const string API::maptostr(const parametermap &map, const bool &firstparam)
{
    string result = "";
    char delim = '?';
    if (!firstparam)
    {
        delim = '&';
    }

    for (const auto &it : map)
    {
        if (it.second.size() == 1)
        {
            result += (delim + it.first + "=" + urlencode(it.second.front()));
            if (delim == '?')
            {
                delim = '&';
            }
        }
        else
        {
            for (const string &str : it.second)
            {
                result += (delim + it.first + "[]=" + urlencode(str));
                if (delim == '?')
                {
                    delim = '&';
                }
            }
        }
    }

    ttdebug << "Constructed parameter string: " << result << '\n';
    return result;
}

const curlpp::Forms API::maptoformdata(const parametermap &map)
{
    curlpp::Forms formdata;

    if (map.size() == 0)
    {
        return formdata;
    }

    for (const auto &it : map)
    {
        if (it.second.size() == 1)
        {   // If the file is not base64-encoded, treat as filename
            if ((it.first == "avatar" ||
                it.first == "header" ||
                it.first == "file") &&
                it.second.front().substr(0, 4).compare("data") != 0)
             {
                ttdebug << it.first << ": Filename detected.\n";
                formdata.push_back(
                    new curlpp::FormParts::File(it.first, it.second.front()));
             }
             else
             {
                formdata.push_back(
                    new curlpp::FormParts::Content(it.first, it.second.front()));
            }
        }
        else
        {
            for (const string &str : it.second)
            {
                formdata.push_back(new curlpp::FormParts::Content(it.first + "[]",
                                                               str));
            }
        }
    }

    return formdata;
}

// const string API::register_app(const std::string &instance,
//                                const std::string &client_name,
//                                const std::string &redirect_uris,
//                                const std::string &scopes,
//                                const std::string &website)
// {
//     API::parametermap parameters =
//     {
//         { "client_name", { client_name } },
//         { "redirect_uris", { redirect_uris } },
//         { "scopes", { scopes } },
//         { "website", { website } }
//     };

//     string answer;
//     std::uint16_t ret = post(API::v1::apps, parameters, answer);
    
// }
