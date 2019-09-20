/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
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
using std::cerr;
using std::to_string;

void API::get_stream(const Mastodon::API::v1 &call,
                     const parameters &params,
                     std::unique_ptr<Mastodon::API::http> &ptr,
                     string &stream)
{
    string strcall = "";

    switch (call)
    {
    case Mastodon::API::v1::streaming_user:
    {
        strcall = "/api/v1/streaming/user";
        break;
    }
    case v1::streaming_public:
    {
        strcall = "/api/v1/streaming/public";
        break;
    }
    case v1::streaming_public_local:
    {
        strcall = "/api/v1/streaming/public/local";
        break;
    }
    case v1::streaming_hashtag:
    {
        strcall = "/api/v1/streaming/hashtag";
        break;
    }
    case v1::streaming_hashtag_local:
    {
        strcall = "/api/v1/streaming/hashtag/local";
        break;
    }
    case v1::streaming_list:
    {
        strcall = "/api/v1/streaming/list";
        break;
    }
    case v1::streaming_direct:
    {
        strcall = "/api/v1/streaming/direct";
        break;
    }
    default:
    {
        const uint8_t err = static_cast<uint8_t>(error::INVALID_ARGUMENT);
        ttdebug << "ERROR: Invalid call.\n";
        stream = "event: ERROR\ndata: "
            "{\"error_code\":" + to_string(err) + "}\n";
        return;
    }
    }

    if (params.size() > 0)
    {
        strcall += maptostr(params);
    }

    return get_stream(strcall, ptr, stream);
}

void API::get_stream(const Mastodon::API::v1 &call,
                     std::unique_ptr<Mastodon::API::http> &ptr,
                     string &stream)
{
    return get_stream(call, {}, ptr, stream);
}

void API::get_stream(const std::string &call, std::unique_ptr<http> &ptr,
                     string &stream)
{
    ptr = std::make_unique<http>(*this, _instance, _access_token);
    return ptr->request_stream(call, stream);
}
