/*  This file is part of mastodon-cpp.
 *  Copyright © 2018 tastytea <tastytea@tastytea.de>
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
#include "debug.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;

return_call API::del(const Mastodon::API::v1 &call,
                     const parameters &params)
{
    string strcall = "";
    string strid = "";

    // The ID is part of the path
    const parameters::const_iterator &it_id = params.find("id");
    const parameters::const_iterator &it_aid = params.find("accountid");
    if (it_id != params.end())
    {
        strid = it_id->values[0];
    }
    else if (it_aid != params.end())
    {
        strid = it_aid->values[0];
    }

    switch (call)
    {
    case v1::domain_blocks:
    {
        strcall = "/api/v1/domain_blocks";
        break;
    }
    case v1::lists_id:
    {
        strcall = "/api/v1/lists/" + strid;
        break;
    }
    case v1::lists_id_accounts:
    {
        strcall = "/api/v1/lists/" + strid + "/accounts";
        break;
    }
    case v1::statuses_id:
    {
        strcall = "/api/v1/statuses/" + strid;
        break;
    }
    case v1::push_subscription:
    {
        strcall = "/api/v1/push/subscription";
        break;
    }
    case v1::filters_id:
    {
        strcall = "/api/v1/filters/" + strid;
        break;
    }
    case v1::suggestions_accountid:
    {
        strcall = "/api/v1/suggestions/" + strid;
        break;
    }
    default:
    {
        ttdebug << "ERROR: Invalid argument.\n";
        return { 22, "Invalid argument", 0, "" };
    }
    }

    return del(strcall, params);
}

return_call API::del(const std::string &call, const parameters &params)
{

    return _http.request(http_method::DELETE, call, *maptoformdata(params));
}
