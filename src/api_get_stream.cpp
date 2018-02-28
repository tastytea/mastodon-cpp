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
#include <memory>
#include "macros.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;
using std::string;
using std::cerr;

const std::uint16_t API::get_stream(const Mastodon::API::v1 &call,
                                    const string &argument,
                                    string &answer,
                                    std::unique_ptr<Mastodon::API::http> &ptr)
{
    string strcall = "";
    const string argument_encoded = curlpp::escape(argument);

    switch (call)
    {
        case v1::streaming_hashtag:
            strcall = "/api/v1/streaming/hashtag?tag=" + argument_encoded;
            break;
        case v1::streaming_list:
            strcall = "/api/v1/streaming/list?list=" + argument_encoded;
            break;
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 11;
            break;
    }

    ptr = std::make_unique<http>(*this, _instance, _access_token);
    return ptr->request_sync(http::method::GET_STREAM, strcall, answer);
}

const std::uint16_t API::get_stream(const Mastodon::API::v1 &call,
                                    string &answer,
                                    std::unique_ptr<Mastodon::API::http> &ptr)
{
    string strcall = "";

    switch (call)
    {
        case v1::streaming_user:
            strcall = "/api/v1/streaming/user";
            break;
        case v1::streaming_public:
            strcall = "/api/v1/streaming/public";
            break;
        case v1::streaming_public_local:
            strcall = "/api/v1/streaming/public/local";
            break;
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 11;
            break;
    }

    ptr = std::make_unique<http>(*this, _instance, _access_token);
    return ptr->request_sync(http::method::GET_STREAM, strcall, answer);
}

const std::uint16_t API::get_stream(const std::string &call, string &answer,
                                    std::unique_ptr<http> &ptr)
{
    ptr = std::make_unique<http>(*this, _instance, _access_token);
    return ptr->request_sync(http::method::GET_STREAM, call, answer);
}
