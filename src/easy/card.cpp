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
#include "card.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Card = Easy::Card;
using std::string;
using std::uint64_t;

Card::Card(const string &json)
: Entity(json)
{}

Card::Card()
: Entity()
{}

const string Card::author_name() const
{
    return get_string("author_name");
}

const string Card::author_url() const
{
    return get_string("author_url");
}

const string Card::description() const
{
    return get_string("description");
}

const uint64_t Card::height() const
{
    return get_uint64("height");
}

const string Card::html() const
{
    return get_string("html");
}

const string Card::image() const
{
    return get_string("image");
}

const string Card::provider_name() const
{
    return get_string("provider_name");
}

const string Card::provider_url() const
{
    return get_string("provider_url");
}

const string Card::title() const
{
    return get_string("title");
}

const Easy::card_type Card::type() const
{
    const string strtype = get_string("type");
    if (strtype.compare("link") == 0)
        return card_type::link;
    else if (strtype.compare("photo") == 0)
        return card_type::photo;
    else if (strtype.compare("video") == 0)
        return card_type::video;
    else if (strtype.compare("rich") == 0)
        return card_type::rich;

    return card_type::unknown;
}

const string Card::url() const
{
    return get_string("url");
}

const uint64_t Card::width() const
{
    return get_uint64("width");
}
