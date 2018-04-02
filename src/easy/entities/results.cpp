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

#include <jsoncpp/json/json.h>
#include "results.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Results = Easy::Results;

Results::Results(const string &json)
: Entity(json)
{}

Results::Results()
: Entity()
{}

const std::vector<Easy::Account> Results::accounts() const
{
    const Json::Value node = get("accounts");
    if (node.isArray())
    {
        std::vector<Easy::Account> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(Easy::Account(value.toStyledString()));
        }
        return vec;
    }

    ttdebug << "Could not get data: accounts\n";
    return {};
}

const std::vector<Easy::Status> Results::statuses() const
{
    const Json::Value node = get("statuses");
    if (node.isArray())
    {
        std::vector<Easy::Status> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(Easy::Status(value.toStyledString()));
        }
        return vec;
    }

    ttdebug << "Could not get data: statuses\n";
    return {};
}

const std::vector<string> Results::hashtags() const
{
    return get_vector("hashtags");
}
