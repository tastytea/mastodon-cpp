/*  This file is part of mastodon-cpp.
 *  Copyright © 2019 tastytea <tastytea@tastytea.de>
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

#include <vector>
#include <algorithm>
#include "filter.hpp"

using std::vector;
using namespace Mastodon;
using Filter = Easy::Filter;

bool Filter::valid() const
{
    return Entity::check_valid(
        {
            "id",
            "phrase",
            "context",
            "irreversible",
            "whole_word"
        });
}

const string Filter::id() const
{
    return get_string("id");
}

const string Filter::phrase() const
{
    return get_string("phrase");
}

const vector<Easy::context_type> Filter::context() const
{
    const Json::Value node = get("context");
    if (node.isArray())
    {
        vector<Easy::context_type> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           {
                               const string strtype = value.asString();
                               if (strtype == "home")
                                   return Easy::context_type::Home;
                               else if (strtype == "notifications")
                                   return Easy::context_type::Notifications;
                               else if (strtype == "public")
                                   return Easy::context_type::Public;
                               else if (strtype == "thread")
                                   return Easy::context_type::Thread;
                               else
                                   return context_type::Undefined;
                           });
        return vec;
    }

    return {};
}

const Easy::time Filter::expires_at() const
{
    return get_time("expires_at");
}

bool Filter::irreversible() const
{
    return get_bool("irreversible");
}

bool Filter::whole_word() const
{
    return get_bool("whole_word");
}
