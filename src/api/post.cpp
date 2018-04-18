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

const uint_fast16_t API::post(const Mastodon::API::v1 &call,
                              const parametermap &parameters, string &answer)
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
        case v1::apps:
            strcall = "/api/v1/apps";
            break;
        case v1::domain_blocks:
            strcall = "/api/v1/domain_blocks";
            break;
        case v1::follows:
            strcall = "/api/v1/follows";
            break;
        case v1::lists:
            strcall = "/api/v1/lists";
            break;
        case v1::media:
            strcall = "/api/v1/media";
            break;
        case v1::notifications_clear:
            strcall = "/api/v1/notifications/clear";
            break;
        case v1::notifications_dismiss:
            strcall = "/api/v1/notifications/dismiss";
            break;
        case v1::reports:
            strcall = "/api/v1/reports";
            break;
        case v1::statuses:
            strcall = "/api/v1/statuses";
            break;
        case v1::accounts_id_follow:
            strcall = "/api/v1/accounts/" + strid + "/follow";
            break;
        case v1::accounts_id_unfollow:
            strcall = "/api/v1/accounts/" + strid + "/unfollow";
            break;
        case v1::accounts_id_block:
            strcall = "/api/v1/accounts/" + strid + "/block";
            break;
        case v1::accounts_id_unblock:
            strcall = "/api/v1/accounts/" + strid + "/unblock";
            break;
        case v1::accounts_id_mute:
            strcall = "/api/v1/accounts/" + strid + "/mute";
            break;
        case v1::accounts_id_unmute:
            strcall = "/api/v1/accounts/" + strid + "/unmute";
            break;
        case v1::follow_requests_id_authorize:
            strcall = "/api/v1/folow_requests/" + strid + "/authorize";
            break;
        case v1::follow_requests_id_reject:
            strcall = "/api/v1/folow_requests/" + strid + "/reject";
            break;
        case v1::lists_id_accounts:
            strcall = "/api/v1/lists/" + strid + "/accounts";
            break;
        case v1::statuses_id_reblog:
            strcall = "/api/v1/statuses/" + strid + "/reblog";
            break;
        case v1::statuses_id_unreblog:
            strcall = "/api/v1/statuses/" + strid + "/unreblog";
            break;
        case v1::statuses_id_favourite:
            strcall = "/api/v1/statuses/" + strid + "/favourite";
            break;
        case v1::statuses_id_unfavourite:
            strcall = "/api/v1/statuses/" + strid + "/unfavourite";
            break;
        case v1::statuses_id_pin:
            strcall = "/api/v1/statuses/" + strid + "/pin";
            break;
        case v1::statuses_id_unpin:
            strcall = "/api/v1/statuses/" + strid + "/unpin";
            break;
        case v1::statuses_id_mute:
            strcall = "/api/v1/statuses/" + strid + "/mute";
            break;
        case v1::statuses_id_unmute:
            strcall = "/api/v1/statuses/" + strid + "/unmute";
            break;
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 11;
            break;
    }

    return post(strcall, parameters, answer);
}

const uint_fast16_t API::post(const Mastodon::API::v1 &call, string &answer)
{
    const parametermap p;
    return post(call, p, answer);
}

const uint_fast16_t API::post(const string &call,
                              const parametermap &parameters, string &answer)
{

    return _http.request(http::method::POST, call,
                         maptoformdata(parameters), answer);
}


// ↓↓ DEPRECATED ↓↓

const uint_fast16_t API::post(const Mastodon::API::v1 &call,
                              const string &argument,
                              const parametermap &parameters, string &answer)
{
    parametermap newparameters = parameters;

    // Emulate old behaviour
    switch (call)
    {
        default:
            newparameters["id"] = { argument };
            break;
    }

    return post(call, newparameters, answer);
}

const uint_fast16_t API::post(const Mastodon::API::v1 &call,
                              const string &argument, string &answer)
{
    const parametermap p;
    return post(call, argument, p, answer);
}
