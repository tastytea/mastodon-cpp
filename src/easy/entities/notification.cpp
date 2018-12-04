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

#include "notification.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Notification = Easy::Notification;

Notification::Notification(const string &json)
: Entity(json)
{}

Notification::Notification()
: Entity()
{}

bool Notification::valid() const
{
    const std::vector<string> attributes =
    {{
        "id",
        "type",
        "created_at",
        "account"
    }};

    return Entity::check_valid(attributes);
}

const Easy::Account Notification::account() const
{
    const Json::Value node = get("account");
    if (node.isObject())
    {
        return Easy::Account(node.toStyledString());
    }

    ttdebug << "Could not get data: account\n";
    return Easy::Account();
}

const system_clock::time_point Notification::created_at() const
{
    return get_time_point("created_at");
}

uint_fast64_t Notification::id() const
{
    return stouint64(get_string("id"));
}

const Easy::Status Notification::status() const
{
    const Json::Value node = get("status");
    if (node.isObject())
    {
        return Easy::Status(node.toStyledString());
    }

    ttdebug << "Could not get data: status\n";
    return Easy::Status();
}

Easy::notification_type Notification::type() const
{
    const string strtype = get_string("type");
    if (strtype.compare("mention") == 0)
        return notification_type::Mention;
    else if (strtype.compare("reblog") == 0)
        return notification_type::Reblog;
    else if (strtype.compare("favourite") == 0)
        return notification_type::Favourite;
    else if (strtype.compare("follow") == 0)
        return notification_type::Follow;

    return notification_type::Undefined;
}
