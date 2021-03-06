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

#include "relationship.hpp"

using namespace Mastodon;
using Relationship = Easy::Relationship;

bool Relationship::valid() const
{
    return Entity::check_valid(
        {
            "id",
            "following",
            "followed_by",
            "blocking",
            "muting",
            "muting_notifications",
            "requested",
            "domain_blocking",
            "showing_reblogs",
            "endorsed"
        });
}

bool Relationship::blocking() const
{
    return get_bool("blocking");
}

bool Relationship::domain_blocking() const
{
    return get_bool("domain_blocking");
}

bool Relationship::endorsed() const
{
    return get_bool("endorsed");
}

bool Relationship::followed_by() const
{
    return get_bool("followed_by");
}

bool Relationship::following() const
{
    return get_bool("following");
}

const string Relationship::id() const
{
    return get_string("id");
}

bool Relationship::muting() const
{
    return get_bool("muting");
}

bool Relationship::muting_notifications() const
{
    return get_bool("muting_notifications");
}

bool Relationship::requested() const
{
    return get_bool("requested");
}

bool Relationship::showing_notifications() const
{
    return get_bool("showing_notifications");
}

bool Relationship::showing_reblogs() const
{
    return get_bool("showing_reblogs");
}
