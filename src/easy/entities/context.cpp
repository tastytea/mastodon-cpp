/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
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

#include <algorithm>
#include "context.hpp"
#include "debug.hpp"

using namespace Mastodon;
using Context = Easy::Context;

bool Context::valid() const
{
    return Entity::check_valid(
        {
            "ancestors",
            "descendants"
        });
}

const std::vector<Easy::Status> Context::ancestors() const
{
    const Json::Value node = get("ancestors");
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

const std::vector<Easy::Status> Context::descendants() const
{
    const Json::Value node = get("descendants");
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
