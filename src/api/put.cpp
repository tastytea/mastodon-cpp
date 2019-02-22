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
#include "debug.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;

return_call API::put(const Mastodon::API::v1 &call,
                     const parametermap &parameters)
{
    string strcall = "";
    string strid = "";

    // The ID is part of the path
    const auto &it = parameters.find("id");
    if (it != parameters.end())
    {
        strid = it->second[0];
    }

    switch (call)
    {
        case v1::lists_id:
            strcall = "/api/v1/lists/" + strid;
            break;
        case v1::media_id:
            strcall = "/api/v1/media/" + strid;
            break;
        case v1::push_subscription:
            strcall = "/api/v1/push/subscription";
            break;
        default:
            ttdebug << "ERROR: Invalid argument.\n";
            return { 22, "Invalid argument", 0, "" };
            break;
    }

    return put(strcall, parameters);
}

return_call API::put(const string &call, const parametermap &parameters)
{

    return _http.request(http::method::PUT, call, maptoformdata(parameters));
}
