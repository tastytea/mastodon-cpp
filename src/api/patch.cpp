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
const std::uint16_t API::patch(const Mastodon::API::v1 &call,
                               const parametermap &parameters,
                               string &answer)
{
    string strcall = "";
    switch (call)
    {
        case v1::accounts_update_credentials:
            strcall = "/api/v1/accounts/update_credentials";
            break;
        default:
            ttdebug << "ERROR: Invalid call.\n";
            return 11;
            break;
    }

    return _http.request(API::http::method::PATCH,
                         strcall, maptoformdata(parameters), answer);
}
