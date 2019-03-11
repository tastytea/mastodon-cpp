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

#include "context.hpp"
#include "debug.hpp"

using namespace Mastodon;
using Context = Easy::Context;

bool Context::valid() const
{
    const std::vector<string> attributes =
    {{
        "ancestors",
        "descendants"
    }};

    return Entity::check_valid(attributes);
}

const std::vector<Easy::Status> Context::ancestors() const
{
    const Json::Value node = get("ancestors");
    if (node.isArray())
    {
        std::vector<Easy::Status> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(Easy::Status(value.toStyledString()));
        }
        return vec;
    }

    ttdebug << "Could not get data: ancestors\n";
    return {};
}

const std::vector<Easy::Status> Context::descendants() const
{
    const Json::Value node = get("descendants");
    if (node.isArray())
    {
        std::vector<Easy::Status> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(Easy::Status(value.toStyledString()));
        }
        return vec;
    }

    ttdebug << "Could not get data: descendants\n";
    return {};
}
