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
#include <curlpp/cURLpp.hpp>
#include "macros.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;
using std::string;

const std::uint16_t API::put(const Mastodon::API::v1 &call,
                             const string &argument,
                             const parametermap &parameters, string &answer)
{
    string strcall = "";
    const string argument_encoded = curlpp::escape(argument);

    switch (call)
    {
        case v1::lists_id:
            strcall = "/api/v1/lists/" + argument_encoded;
            break;
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 1;
            break;
    }

    return _http.request_sync(http::method::PUT, strcall,
                              maptoformdata(parameters), answer);
}

const std::uint16_t API::put(const std::string &call,
                             const parametermap &parameters, string &answer)
{

    return _http.request_sync(http::method::PUT, call,
                              maptoformdata(parameters), answer);
}
