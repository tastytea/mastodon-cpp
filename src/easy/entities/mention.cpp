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

#include "mention.hpp"

using namespace Mastodon;
using Mention = Easy::Mention;

bool Mention::valid() const
{
    const std::vector<string> attributes =
    {{
        "url",
        "username",
        "acct",
        "id"
    }};

    return Entity::check_valid(attributes);
}

const string Mention::acct() const
{
    return get_string("acct");
}

const string Mention::id() const
{
    return get_string("id");
}

const string Mention::url() const
{
    return get_string("url");
}

const string Mention::username() const
{
    return get_string("username");
}
