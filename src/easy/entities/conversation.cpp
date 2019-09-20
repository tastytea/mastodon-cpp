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
#include "conversation.hpp"
#include "debug.hpp"

using namespace Mastodon;
using Conversation = Easy::Conversation;

bool Conversation::valid() const
{
    return Entity::check_valid(
        {
            "id",
            "accounts",
            "unread"
        });
}

const string Conversation::id() const
{
    return get_string("id");
}

const std::vector<Easy::Account> Conversation::accounts() const
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

const Easy::Status Conversation::last_status() const
{
    const Json::Value &node = get("last_status");
    if (!node.isNull())
    {
        return Easy::Status(node);
    }

    return {};
}

bool Conversation::unread() const
{
    return get_bool("unread");
}
