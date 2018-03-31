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

#include "relationship.hpp"

using namespace Mastodon;
using Relationship = Easy::Relationship;

Relationship::Relationship(const string &json)
: Entity(json)
{}

Relationship::Relationship()
: Entity()
{}

const bool Relationship::blocking() const
{
    return get_bool("blocking");
}

const bool Relationship::domain_blocking() const
{
    return get_bool("domain_blocking");
}

const bool Relationship::followed_by() const
{
    return get_bool("followed_by");
}

const bool Relationship::following() const
{
    return get_bool("following");
}

const uint64_t Relationship::id() const
{
    return get_uint64("id");
}

const bool Relationship::muting() const
{
    return get_bool("muting");
}

const bool Relationship::muting_notifications() const
{
    return get_bool("muting_notifications");
}

const bool Relationship::requested() const
{
    return get_bool("requested");
}
