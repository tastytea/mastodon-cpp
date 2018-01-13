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
using std::cerr;
const std::uint16_t API::get(const Mastodon::API::v1 &call, string &answer)
{
    const std::vector<string> v{};
    return get(call, v, answer);
}

const std::uint16_t API::get(const Mastodon::API::v1 &call,
                      const std::vector<string> &parameters, string &answer)
{
    string strcall = "";
    switch (call)
    {
        case v1::accounts_verify_credentials:
            strcall = "/api/v1/accounts/verify_credentials";
            break;
        case v1::blocks:
            strcall = "/api/v1/blocks";
            break;
        case v1::domain_blocks:
            strcall = "/api/v1/domain_blocks";
            break;
        case v1::favourites:
            strcall = "/api/v1/favourites";
            break;
        case v1::follow_requests:
            strcall = "/api/v1/follow_requests";
            break;
        case v1::instance:
            strcall = "/api/v1/instance";
            break;
        case v1::custom_emojis:
            strcall = "/api/v1/custom_emojis";
            break;
        case v1::lists:
            strcall = "/api/v1/lists";
            break;
        case v1::mutes:
            strcall = "/api/v1/mutes";
            break;
        case v1::notifications:
            strcall = "/api/v1/notifications";
            break;
        case v1::reports:
            strcall = "/api/v1/reports";
            break;
        case v1::timelines_home:
            strcall = "/api/v1/timelines/home";
            break;
        case v1::timelines_public:
            strcall = "/api/v1/timelines/public";
            break;
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 1;
            break;
    }

    if (parameters.size() > 0)
    {
        char delim = '?';
        for (const string p : parameters)
        {
            strcall += delim + p;
            if (delim == '?')
            {
                delim = '&';
            }
        }
    }

    return _http.request_sync(http::method::GET, strcall, answer);
}

const std::uint16_t API::get(const Mastodon::API::v1 &call,
                      const string &argument, string &answer)
{
    const std::vector<string> v;
    return get(call, argument, v, answer);
}
const std::uint16_t API::get(const Mastodon::API::v1 &call,
                      const string &argument,
                      const std::vector<string> &parameters, string &answer)
{
    string strcall = "";
    char delim = '?';

    switch (call)
    {
        case v1::accounts_id:
            strcall = "/api/v1/accounts/" + argument;
            break;
        case v1::accounts_id_followers:
            strcall = "/api/v1/accounts/" + argument + "/followers";
            break;
        case v1::accounts_id_following:
            strcall = "/api/v1/accounts/" + argument + "/following";
            break;
        case v1::accounts_id_statuses:
            strcall = "/api/v1/accounts/" + argument + "/statuses";
            break;
        case v1::accounts_relationships:
            strcall = "/api/v1/accounts/relationships?id=" + argument;
            delim = '&';
            break;
        case v1::accounts_search:
            strcall = "/api/v1/accounts/search?q=" + argument;
            delim = '&';
            break;
        case v1::accounts_id_lists:
            strcall = "/api/v1/accounts/" + argument + "/lists";
            break;
        case v1::lists_id_accounts:
            strcall = "/api/v1/lists/" + argument + "/accounts";
            break;
        case v1::lists_id:
            strcall = "/api/v1/lists/" + argument;
            break;
        case v1::notifications_id:
            strcall = "/api/v1/notifications/" + argument;
            break;
        case v1::search:
            strcall = "/api/v1/search?q=" + argument;
            delim = '&';
            break;
        case v1::statuses_id:
            strcall = "/api/v1/statuses/" + argument;
            break;
        case v1::statuses_id_context:
            strcall = "/api/v1/statuses/" + argument + "/context";
            break;
        case v1::statuses_id_card:
            strcall = "/api/v1/statuses/" + argument + "/card";
            break;
        case v1::statuses_id_reblogged_by:
            strcall = "/api/v1/statuses/" + argument + "/reblogged_by";
            break;
        case v1::statuses_id_favourited_by:
            strcall = "/api/v1/statuses/" + argument + "/favourited_by";
            break;
        case v1::timelines_tag_hashtag:
            strcall = "/api/v1/timelines/tag/" + argument;
            break;
        case v1::timelines_list_list_id:
            strcall = "/api/v1/timelines/list/" + argument;
            break;
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 1;
            break;
    }

    if (parameters.size() > 0)
    {
        for (const string p : parameters)
        {
            strcall += delim + p;
            if (delim == '?')
            {
                delim = '&';
            }
        }
    }

    return _http.request_sync(http::method::GET, strcall, answer);
}

const std::uint16_t API::get(const std::string &call, string &answer)
{
    return _http.request_sync(http::method::GET, call, answer);
}
