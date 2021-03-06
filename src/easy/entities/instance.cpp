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

#include <jsoncpp/json/json.h>
#include "instance.hpp"
#include "account.hpp"
#include "debug.hpp"

using namespace Mastodon;
using Instance = Easy::Instance;

bool Instance::valid() const
{
    return Entity::check_valid(
        {
            "uri",
            "title",
            "description",
            "email",
            "version",
            "urls",
            "stats",
            "languages"
        });
}

const Easy::Account Instance::contact_account() const
{
    const Json::Value node = get("contact_account");
    if (node.isObject())
    {
        return Easy::Account(node);
    }

    return Easy::Account();
}

const string Instance::description() const
{
    return get_string("description");
}

const string Instance::email() const
{
    return get_string("email");
}

const std::vector<string> Instance::languages() const
{
    return get_vector("languages");
}

const Easy::stats_type Instance::stats() const
{
    Easy::stats_type s;
    s.user_count = get_uint64("stats.user_count");
    s.status_count = get_uint64("stats.status_count");
    s.domain_count = get_uint64("stats.domain_count");
    return s;
}

const string Instance::title() const
{
    return get_string("title");
}

const string Instance::uri() const
{
    return get_string("uri");
}

const Easy::urls_type Instance::urls() const
{
    return { get_string("urls.streaming_api") };
}

const string Instance::version() const
{
    return get_string("version");
}

const string Instance::thumbnail() const
{
    return get_string("thumbnail");
}

uint64_t Instance::max_toot_chars() const
{
    const uint64_t max_chars = get_uint64("max_toot_chars");
    if (was_set())
    {
        return max_chars;
    }
    else
    {
        return 500;
    }
}
