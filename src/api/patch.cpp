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

return_call API::patch(const Mastodon::API::v1 &call,
                       const parameters &params)
{
    string strcall = "";
    switch (call)
    {
        case v1::accounts_update_credentials:
            strcall = "/api/v1/accounts/update_credentials";
            break;
        default:
            ttdebug << "ERROR: Invalid argument.\n";
            return { 22, "Invalid argument", 0, "" };
            break;
    }

    return _http.request(http_method::PATCH, strcall, *maptoformdata(params));
}
