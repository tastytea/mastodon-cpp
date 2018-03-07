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
#include <regex>
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

const string API::get_instance() const
{
    return _instance;
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
            result += (delim + it.first + "=" + curlpp::escape(it.second.front()));
            if (delim == '?')
            {
                delim = '&';
            }
        }
        else
        {
            for (const string &str : it.second)
            {
                result += (delim + it.first + "[]=" + curlpp::escape(str));
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

const std::string API::urlencode(const std::string &str) const
{
    return curlpp::escape(str);
}

const std::uint16_t API::register_app1(const string &instance,
                                       const string &client_name,
                                       const string &redirect_uri,
                                       const string &scopes,
                                       const string &website,
                                       string &client_id,
                                       string &client_secret,
                                       string &url)
{
    return register_app1(client_name, redirect_uri, scopes, website,
                  client_id, client_secret, url);
}
const std::uint16_t API::register_app1(const string &client_name,
                                       const string &redirect_uri,
                                       const string &scopes,
                                       const string &website,
                                       string &client_id,
                                       string &client_secret,
                                       string &url)
{
    API::parametermap parameters =
    {
        { "client_name", { client_name } },
        { "redirect_uris", { redirect_uri } },
        { "scopes", { scopes } },
        { "website", { website } }
    };

    string answer;
    std::uint16_t ret = post(API::v1::apps, parameters, answer);

    if (ret == 0)
    {
        std::smatch match;
        std::regex reid("client_id\":\"([0-9a-fA-F]+)\"");
        std::regex resecret("client_secret\":\"([0-9a-fA-F]+)\"");

        std::regex_search(answer, match, reid);
        client_id = match[1].str();
        std::regex_search(answer, match, resecret);
        client_secret = match[1].str();

        url = "https://" + _instance + "/oauth/authorize" +
              "?scope=" + curlpp::escape(scopes) + "&response_type=code" +
              "&redirect_uri=" + curlpp::escape(redirect_uri) +
              "&client_id=" + client_id;
        if (!website.empty())
        {
            url += "&website=" + website;
        }

        return 0;
    }
    else if (ret == 13)
    {
        url = answer;
        return ret;
    }
    else
    {
        std::cerr << "Error code: " << ret << '\n';
        return ret;
    }
    
}

const std::uint16_t API::register_app2(const string &instance,
                                       const string &client_id,
                                       const string &client_secret,
                                       const string &redirect_uri,
                                       const string &code,
                                       string &access_token)
{
    return register_app2(client_id, client_secret, redirect_uri, code, access_token);
}

const std::uint16_t API::register_app2(const string &client_id,
                                       const string &client_secret,
                                       const string &redirect_uri,
                                       const string &code,
                                       string &access_token)
{
    API::parametermap parameters =
    {
        { "client_id", { client_id } },
        { "client_secret", { client_secret } },
        { "grant_type", { "authorization_code" } },
        { "redirect_uri", { redirect_uri } },
        { "code", { code } },
    };

    std::string answer;
    std::uint16_t ret = post("/oauth/token", parameters, answer);
    if (ret == 0)
    {
        std::smatch match;
        std::regex retoken("access_token\":\"([0-9a-fA-F]+)\"");

        std::regex_search(answer, match, retoken);
        access_token = match[1].str();
        _access_token = access_token;

        return 0;
    }
    else
    {
        std::cerr << "Error code: " << ret << '\n';
        return ret;
    }
}

const string API::get_header(const std::string &header) const
{
    string headers;
    _http.get_headers(headers);
    size_t startpos = headers.find(header);
    if (startpos != std::string::npos)
    {
        startpos = headers.find(':', startpos) + 2;
        size_t endpos = headers.find("\r\n", startpos);
        return headers.substr(startpos, endpos - startpos);
    }

    return "";
}
