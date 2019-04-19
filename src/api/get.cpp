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
#include <algorithm>
#include "debug.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;

const return_call API::get(const Mastodon::API::v1 &call,
                           const parameters &params)
{
    string strcall = "";
    string strid = "";

    // The ID is part of the path
    const auto &it_id = params.find("id");
    if (it_id != params.end())
    {
        strid = it_id->values[0];
    }

    switch (call)
    {
    case v1::accounts_verify_credentials:
    {
        strcall = "/api/v1/accounts/verify_credentials";
        break;
    }
    case v1::blocks:
    {
        strcall = "/api/v1/blocks";
        break;
    }
    case v1::domain_blocks:
    {
        strcall = "/api/v1/domain_blocks";
        break;
    }
    case v1::favourites:
    {
        strcall = "/api/v1/favourites";
        break;
    }
    case v1::follow_requests:
    {
        strcall = "/api/v1/follow_requests";
        break;
    }
    case v1::instance:
    {
        strcall = "/api/v1/instance";
        break;
    }
    case v1::custom_emojis:
    {
        strcall = "/api/v1/custom_emojis";
        break;
    }
    case v1::lists:
    {
        strcall = "/api/v1/lists";
        break;
    }
    case v1::mutes:
    {
        strcall = "/api/v1/mutes";
        break;
    }
    case v1::notifications:
    {
        strcall = "/api/v1/notifications";
        break;
    }
    case v1::reports:
    {
        strcall = "/api/v1/reports";
        break;
    }
    case v1::timelines_home:
    {
        strcall = "/api/v1/timelines/home";
        break;
    }
    case v1::timelines_public:
    {
        strcall = "/api/v1/timelines/public";
        break;
    }
    case v1::accounts_relationships:
    {
        strcall = "/api/v1/accounts/relationships";
        break;
    }
    case v1::accounts_id:
    {
        strcall = "/api/v1/accounts/" + strid;
        break;
    }
    case v1::accounts_id_followers:
    {
        strcall = "/api/v1/accounts/" + strid + "/followers";
        break;
    }
    case v1::accounts_id_following:
    {
        strcall = "/api/v1/accounts/" + strid + "/following";
        break;
    }
    case v1::accounts_id_statuses:
    {
        strcall = "/api/v1/accounts/" + strid + "/statuses";
        break;
    }
    case v1::accounts_search:
    {
        strcall = "/api/v1/accounts/search";
        break;
    }
    case v1::accounts_id_lists:
    {
        strcall = "/api/v1/accounts/" + strid + "/lists";
        break;
    }
    case v1::lists_id_accounts:
    {
        strcall = "/api/v1/lists/" + strid + "/accounts";
        break;
    }
    case v1::lists_id:
    {
        strcall = "/api/v1/lists/" + strid;
        break;
    }
    case v1::notifications_id:
    {
        strcall = "/api/v1/notifications/" + strid;
        break;
    }
    case v1::search:
    {
        strcall = "/api/v1/search";
        break;
    }
    case v1::statuses_id:
    {
        strcall = "/api/v1/statuses/" + strid;
        break;
    }
    case v1::statuses_id_context:
    {
        strcall = "/api/v1/statuses/" + strid + "/context";
        break;
    }
    case v1::statuses_id_card:
    {
        strcall = "/api/v1/statuses/" + strid + "/card";
        break;
    }
    case v1::statuses_id_reblogged_by:
    {
        strcall = "/api/v1/statuses/" + strid + "/reblogged_by";
        break;
    }
    case v1::statuses_id_favourited_by:
    {
        strcall = "/api/v1/statuses/" + strid + "/favourited_by";
        break;
    }
    case v1::timelines_tag_hashtag:
    {
        // The tag is part of the path
        const auto &it = params.find("tag");
        if (it != params.end())
        {
            strcall = "/api/v1/timelines/tag/" + ::urlencode(it->values[0]);
        }
        else
        {
            ttdebug << "ERROR: Invalid argument.\n";
            return { 22, "Invalid argument", 0, "" };
        }
        break;
    }
    case v1::timelines_list_list_id:
    {
        strcall = "/api/v1/timelines/list/" + strid;
        break;
    }
    case v1::push_subscription:
    {
        strcall = "/api/v1/push/subscription";
        break;
    }
    case v1::endorsements:
    {
        strcall = "/api/v1/endorsements";
        break;
    }
    case v1::bookmarks:
    {
        strcall = "/api/v1/bookmarks";
        break;
    }
    case v1::apps_verify_credentials:
    {
        strcall = "/api/v1/apps/verify_credentials";
        break;
    }
    case v1::filters:
    {
        strcall = "/api/v1/filters";
        break;
    }
    case v1::filters_id:
    {
        strcall = "/api/v1/filters/" + strid;
        break;
    }
    case v1::suggestions:
    {
        strcall = "/api/v1/suggestions";
        break;
    }
    default:
    {
        ttdebug << "ERROR: Invalid argument.\n";
        return { 22, "Invalid argument", 0, "" };
    }
    }

    if (params.size() > 0)
    {
        // Delete the parameters that are already in strcall
        const parameters newparams = delete_params(params, { "id", "tag" });
        strcall += maptostr(newparams);
    }

    return get(strcall);
}

const return_call API::get(const Mastodon::API::v2 &call,
                           const parameters &params)
{
    string strcall = "";
    string strid = "";

    // The ID is part of the path
    const auto &it = params.find("id");
    if (it != params.end())
    {
        strid = it->values[0];
    }

    switch (call)
    {
        case v2::search:
        {
            strcall = "/api/v2/search";
            break;
        }
        default:
        {
            ttdebug << "ERROR: Invalid argument.\n";
            return { 22, "Invalid argument", 0, "" };
        }
    }

    if (params.size() > 0)
    {
        // Delete the parameterss that are already in strcall
        const parameters newparams = delete_params(params, { "id", "tag" });
        strcall += maptostr(newparams);
    }

    return get(strcall);
}

const return_call API::get(const Mastodon::API::v1 &call)
{
    return get(call, {});
}

const return_call API::get(const std::string &call)
{
    return _http.request(http_method::GET, call);
}
