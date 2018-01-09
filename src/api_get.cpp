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
const string API::get(const Mastodon::API::v1 &method)
{
    const std::vector<string> v{};
    return get(method, v);
}

const string API::get(const Mastodon::API::v1 &method,
                      const std::vector<string> &parameters)
{
    string strmethod = "";
    switch (method)
    {
        case v1::accounts_verify_credentials:
            strmethod = "/api/v1/accounts/verify_credentials";
            break;
        default:
            cerr << "ERROR: Invalid method.\n";
            break;
    }

    string answer;
    _http.request_sync(http::method::GET, strmethod, answer);
    return answer;
}

const string API::get(const Mastodon::API::v1 &method,
                      const string &argument)
{
    const std::vector<string> v;
    return get(method, argument, v);
}
const string API::get(const Mastodon::API::v1 &method,
                      const string &argument,
                      const std::vector<string> &parameters)
{
    string strmethod = "";
    switch (method)
    {
        case v1::accounts_id:
            strmethod = "/api/v1/accounts/" + argument;
            break;
        case v1::accounts_id_followers:
            strmethod = "/api/v1/accounts/" + argument + "/followers";
            break;
        case v1::accounts_id_following:
            strmethod = "/api/v1/accounts/" + argument + "/following";
            break;
        case v1::accounts_id_statuses:
            strmethod = "/api/v1/accounts/" + argument + "/statuses";
            break;
        case v1::accounts_relationships:
            strmethod = "/api/v1/accounts/relationships?id=" + argument;
            break;
        case v1::accounts_search:
            strmethod = "/api/v1/accounts/search?q=" + argument;
            break;
        default:
            cerr << "ERROR: Invalid method.\n";
            return "";
            break;
    }

    string answer;
    _http.request_sync(http::method::GET, strmethod, answer);
    return answer;
}

const string API::get(const std::string &method)
{
    return method;
}
