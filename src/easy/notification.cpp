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
using std::string;
using std::uint64_t;

Notification::Notification(const string &json)
: Entity(json)
{}

Notification::Notification()
: Entity()
{}

const Easy::Account Notification::account() const
{
    const Json::Value node = _tree["account"];
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

const uint64_t Notification::id() const
{
    return get_uint64("id");
}

// const Status Notification::status() const
// {
//     //
// }

const Easy::notification_type Notification::type() const
{
    const string strtype = get_string("type");
    if (strtype.compare("mention") == 0)
        return notification_type::mention;
    else if (strtype.compare("reblog") == 0)
        return notification_type::reblog;
    else if (strtype.compare("favourite") == 0)
        return notification_type::favourite;
    else if (strtype.compare("follow") == 0)
        return notification_type::follow;

    return notification_type::unknown;
}
