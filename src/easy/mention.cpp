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

#include <string>
#include "mention.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Mention = Easy::Mention;
using std::string;
using std::uint64_t;

Mention::Mention(const string &json)
: Entity(json)
{}

Mention::Mention()
: Entity()
{}

const string Mention::acct() const
{
    return get_string("acct");
}

const uint64_t Mention::id() const
{
    return get_uint64("id");
}

const string Mention::url() const
{
    return get_string("url");
}

const string Mention::username() const
{
    return get_string("username");
}
