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
            result += (delim + it.first + "=" + it.second.front());
            if (delim == '?')
            {
                delim = '&';
            }
        }
        else
        {
            for (const string &str : it.second)
            {
                result += (delim + it.first + "[]=" + str);
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
