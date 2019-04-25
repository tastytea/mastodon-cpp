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

#include "pushsubscription.hpp"

using namespace Mastodon;
using PushSubscription = Easy::PushSubscription;

const string PushSubscription::id() const
{
    return get_string("id");
}

bool PushSubscription::valid() const
{
    return Entity::check_valid(
        {
            "id",
            "endpoint",
            "server_key"
        });
}

const string PushSubscription::endpoint() const
{
    return get_string("endpoint");
}

const string PushSubscription::server_key() const
{
    return get_string("server_key");
}

const Easy::alerts PushSubscription::alerts() const
{
    Easy::alerts alerts;
    const Json::Value node = get("alerts");
    for (auto it = node.begin(); it != node.end(); ++it)
    {
        const string &str = it.name();
        Easy::notification_type type;
        if (str.compare("mention") == 0)
        {
            type = notification_type::Mention;
        }
        else if (str.compare("reblog") == 0)
        {
            type = notification_type::Reblog;
        }
        else if (str.compare("favourite") == 0)
        {
            type = notification_type::Favourite;
        }
        else if (str.compare("follow") == 0)
        {
            type = notification_type::Follow;
        }
        else
        {
            type = notification_type::Undefined;
        }

        alerts.push_back({ type, s_to_b(it->asString()) });
    }
    return alerts;
}

bool PushSubscription::s_to_b(const string &str) const
{
    if (str.compare("true") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
