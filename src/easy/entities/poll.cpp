/*  This file is part of mastodon-cpp.
 *  Copyright © 2019 tastytea <tastytea@tastytea.de>
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

#include "poll.hpp"
#include "debug.hpp"

using namespace Mastodon;
using Poll = Easy::Poll;

bool Poll::valid() const
{
    return Entity::check_valid(
        {
            "id",
            "expired",
            "expired",
            "multiple",
            "votes_count",
            "options"
        });
}

const string Poll::id() const
{
    return get_string("id");
}

const Easy::time_type Poll::expires_at() const
{
    return get_time("expires_at");
}

bool Poll::expired() const
{
    return get_bool("expired");
}

bool Poll::multiple() const
{
    return get_bool("multiple");
}

uint64_t Poll::votes_count() const
{
    return get_uint64("votes_count");
}

const vector<Easy::poll_options_type> Poll::options() const
{
    const Json::Value &node = get("options");

    if (node.isArray())
    {
        vector<Easy::poll_options_type> vec_options;
        std::transform(node.begin(), node.end(), std::back_inserter(vec_options),
                       [](const Json::Value &value)
                       {
                           return Easy::poll_options_type(
                               {
                                   value["title"].asString(),
                                   value["votes_count"].asUInt64()
                               });
                       });
        return vec_options;
    }

    return {};
}

bool Poll::voted() const
{
    return get_bool("voted");
}
