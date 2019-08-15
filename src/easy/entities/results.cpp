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

#include <algorithm>
#include <jsoncpp/json/json.h>
#include "results.hpp"

using namespace Mastodon;
using Results = Easy::Results;

bool Results::valid() const
{
    return Entity::check_valid(
        {
            "accounts",
            "statuses",
            "hashtags"
        });
}

const std::vector<Easy::Account> Results::accounts() const
{
    const Json::Value node = get("accounts");
    if (node.isArray())
    {
        std::vector<Easy::Account> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           { return Easy::Account(value); });
        return vec;
    }

    return {};
}

const std::vector<Easy::Status> Results::statuses() const
{
    const Json::Value node = get("statuses");
    if (node.isArray())
    {
        std::vector<Easy::Status> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           { return Easy::Status(value); });
        return vec;
    }

    return {};
}

const std::vector<string> Results::hashtags_v1() const
{
    return get_vector("hashtags");
}

const std::vector<Easy::Tag> Results::hashtags_v2() const
{
    const Json::Value node = get("hashtags");
    if (node.isArray())
    {
        std::vector<Easy::Tag> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           { return Easy::Tag(value); });
        return vec;
    }

    return {};
}
