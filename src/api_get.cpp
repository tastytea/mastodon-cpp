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
#include "mastodon-cpp.hpp"

using namespace Mastodon;
using std::string;
using std::cerr;
const string API::get(const Mastodon::API::v1 &call)
{
    const std::vector<string> v{};
    return get(call, v);
}

const string API::get(const Mastodon::API::v1 &call,
                      const std::vector<string> &parameters)
{
    string strcall = "";
    switch (call)
    {
        case v1::accounts_verify_credentials:
            strcall = "/api/v1/accounts/verify_credentials";
            break;
        default:
            cerr << "ERROR: Invalid call.\n";
            break;
    }

    string answer;
    _http.request_sync(http::method::GET, strcall, answer);
    return answer;
}

const string API::get(const Mastodon::API::v1 &call,
                      const string &argument)
{
    const std::vector<string> v;
    return get(call, argument, v);
}
const string API::get(const Mastodon::API::v1 &call,
                      const string &argument,
                      const std::vector<string> &parameters)
{
    string strcall = "";
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
            break;
        case v1::accounts_search:
            strcall = "/api/v1/accounts/search?q=" + argument;
            break;
        default:
            cerr << "ERROR: Invalid call.\n";
            return "";
            break;
    }

    string answer;
    _http.request_sync(http::method::GET, strcall, answer);
    return answer;
}

const string API::get(const std::string &call)
{
    return call;
}
