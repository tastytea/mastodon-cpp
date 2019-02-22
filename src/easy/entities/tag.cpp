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

#include <sstream>
#include <iomanip>
#include "tag.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Tag = Easy::Tag;

Tag::Tag(const string &json)
: Entity(json)
{}

Tag::Tag()
: Entity()
{}

bool Tag::valid() const
{
    const std::vector<string> attributes =
    {{
        "name",
        "url"
    }};

    return Entity::check_valid(attributes);
}

const string Tag::name() const
{
    return get_string("name");
}

const string Tag::url() const
{
    return get_string("url");
}

const std::vector<Tag::History> Tag::history() const
{
    const Json::Value node = get("history");
    if (node.isArray())
    {
        std::vector<Easy::Tag::History> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(Easy::Tag::History(value.toStyledString()));
        }
        return vec;
    }

    ttdebug << "Could not get data: history\n";
    return {};
}


Tag::History::History(const string &json)
: Entity(json)
{}

Tag::History::History()
: Entity()
{}

bool Tag::History::valid() const
{
    const std::vector<string> attributes =
    {{
        "day",
        "uses",
        "accounts"
    }};

    return Entity::check_valid(attributes);
}

uint64_t Tag::History::accounts()
{
    return stouint64(get_string("accounts"));
}

const system_clock::time_point Tag::History::day()
{
    const Json::Value node = get("day");

    if (node.isString())
    {
        std::chrono::seconds seconds(stouint64(node.asString()));
        return system_clock::time_point(seconds);
    }

    ttdebug << "Could not get data: day\n";
    return system_clock::time_point();
}

uint64_t Tag::History::uses()
{
    return stouint64(get_string("uses"));
}
