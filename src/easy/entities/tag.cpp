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

#include <sstream>
#include <iomanip>
#include <algorithm>
#include "tag.hpp"
#include "debug.hpp"

using namespace Mastodon;
using Tag = Easy::Tag;

bool Tag::valid() const
{
    return Entity::check_valid(
        {
            "name",
            "url"
        });
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
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                       { return Easy::Tag::History(value); });
        return vec;
    }

    ttdebug << "Could not get data: history\n";
    return {};
}

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

uint64_t Tag::History::accounts() const
{
    return get_uint64("accounts");
}

const Easy::time_type Tag::History::day() const
{
    const Json::Value node = get("day");

    if (node.isString())
    {
        std::chrono::seconds seconds(stouint64(node.asString()));
        return {system_clock::time_point(seconds)};
    }

    ttdebug << "Could not get data: day\n";
    return Easy::time_type();
}

uint64_t Tag::History::uses() const
{
    return get_uint64("uses");
}
