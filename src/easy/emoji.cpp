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
#include <sstream>
#include <jsoncpp/json/json.h>
#include "emoji.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Emoji = Easy::Emoji;
using std::string;
using std::uint64_t;

Emoji::Emoji(const string &json)
: Entity(json)
{}

Emoji::Emoji()
: Entity()
{}

const string Emoji::shortcode() const
{
    return get_string("shortcode");
}

const string Emoji::static_url() const
{
    return get_string("static_url");
}

const string Emoji::url() const
{
    return get_string("url");
}
