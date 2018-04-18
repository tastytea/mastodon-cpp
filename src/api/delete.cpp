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

#include <iostream>
#include "macros.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;

const uint_fast16_t API::del(const Mastodon::API::v1 &call,
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
        case v1::domain_blocks:
            strcall = "/api/v1/domain_blocks";
            break;
        case v1::lists_id:
            strcall = "/api/v1/lists/" + strid;
            break;
        case v1::lists_id_accounts:
            strcall = "/api/v1/lists/" + strid + "/accounts";
            break;
        case v1::statuses_id:
            strcall = "/api/v1/statuses/" + strid;
            break;
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 11;
            break;
    }

    string answer;
    return del(strcall, parameters, answer);
}

const uint_fast16_t API::del(const std::string &call,
                              const parametermap &parameters, string &answer)
{

    return _http.request(http::method::DELETE, call,
                         maptoformdata(parameters), answer);
}


// ↓↓ DEPRECATED ↓↓

const uint_fast16_t API::del(const Mastodon::API::v1 &call,
                             const string &argument)
{
    const parametermap p = {};
    return del(call, argument, p);
}

const uint_fast16_t API::del(const Mastodon::API::v1 &call,
                             const string &argument,
                             const parametermap &parameters)
{
    parametermap newparameters = parameters;

    // Emulate old behaviour
    newparameters["id"] = { argument };

    return del(call, parameters);
}
