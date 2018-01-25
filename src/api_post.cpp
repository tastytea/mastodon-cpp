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
#include <string>
#include <vector>
#include "macros.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;
using std::string;

const std::uint16_t API::post(const Mastodon::API::v1 &call, string &answer)
{
    const parametermap p;
    return post(call, p, answer);
}

const std::uint16_t API::post(const Mastodon::API::v1 &call,
                              const parametermap &parameters, string &answer)
{
    string strcall = "";

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
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 1;
            break;
    }

    return _http.request_sync(http::method::POST, strcall,
                              maptoformdata(parameters), answer);
}

const std::uint16_t API::post(const Mastodon::API::v1 &call,
                              const string &argument, string &answer)
{
    const parametermap p;
    return post(call, argument, p, answer);
}
const std::uint16_t API::post(const Mastodon::API::v1 &call,
                              const string &argument,
                              const parametermap &parameters, string &answer)
{
    string strcall = "";
    const string argument_encoded = urlencode(argument);

    switch (call)
    {
        case v1::accounts_id_follow:
            strcall = "/api/v1/accounts/" + argument_encoded + "/follow";
            break;
        case v1::accounts_id_unfollow:
            strcall = "/api/v1/accounts/" + argument_encoded + "/unfollow";
            break;
        case v1::accounts_id_block:
            strcall = "/api/v1/accounts/" + argument_encoded + "/block";
            break;
        case v1::accounts_id_unblock:
            strcall = "/api/v1/accounts/" + argument_encoded + "/unblock";
            break;
        case v1::accounts_id_mute:
            strcall = "/api/v1/accounts/" + argument_encoded + "/mute";
            break;
        case v1::accounts_id_unmute:
            strcall = "/api/v1/accounts/" + argument_encoded + "/unmute";
            break;
        case v1::follow_requests_id_authorize:
            strcall = "/api/v1/folow_requests/" + argument_encoded + "/authorize";
            break;
        case v1::follow_requests_id_reject:
            strcall = "/api/v1/folow_requests/" + argument_encoded + "/reject";
            break;
        case v1::lists_id_accounts:
            strcall = "/api/v1/lists/" + argument_encoded + "/accounts";
            break;
        case v1::statuses_id_reblog:
            strcall = "/api/v1/statuses/" + argument_encoded + "/reblog";
            break;
        case v1::statuses_id_unreblog:
            strcall = "/api/v1/statuses/" + argument_encoded + "/unreblog";
            break;
        case v1::statuses_id_favourite:
            strcall = "/api/v1/statuses/" + argument_encoded + "/favourite";
            break;
        case v1::statuses_id_unfavourite:
            strcall = "/api/v1/statuses/" + argument_encoded + "/unfavourite";
            break;
        case v1::statuses_id_pin:
            strcall = "/api/v1/statuses/" + argument_encoded + "/pin";
            break;
        case v1::statuses_id_unpin:
            strcall = "/api/v1/statuses/" + argument_encoded + "/unpin";
            break;
        case v1::statuses_id_mute:
            strcall = "/api/v1/statuses/" + argument_encoded + "/mute";
            break;
        case v1::statuses_id_unmute:
            strcall = "/api/v1/statuses/" + argument_encoded + "/unmute";
            break;
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 1;
            break;
    }

    return _http.request_sync(http::method::POST, strcall,
                              maptoformdata(parameters), answer);
}

const std::uint16_t API::post(const std::string &call,
                              const parametermap &parameters, string &answer)
{

    return _http.request_sync(http::method::POST, call,
                              maptoformdata(parameters), answer);
}
