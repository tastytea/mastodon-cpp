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

#include "card.hpp"
#include "debug.hpp"

using namespace Mastodon;
using Card = Easy::Card;

bool Card::valid() const
{
    return Entity::check_valid(
        {
            "url",
            "title",
            "description",
            "type"
        });
}

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

const string Card::embed_url() const
{
    return get_string("embed_url");
}

uint64_t Card::height() const
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

Easy::card_type Card::type() const
{
    const string strtype = get_string("type");
    if (strtype == "link")
        return card_type::Link;
    else if (strtype == "photo")
        return card_type::Photo;
    else if (strtype == "video")
        return card_type::Video;
    else if (strtype == "rich")
        return card_type::Rich;
    else
        return card_type::Undefined;
}

const string Card::url() const
{
    return get_string("url");
}

uint64_t Card::width() const
{
    return get_uint64("width");
}
