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
{
    //
}

const string Card::author_name() const
{
    if (_tree["author_name"].isString())
    {
        return _tree["author_name"].asString();
    }

    ttdebug << "Could not get attachment data: author_name\n";
    return "";
}

const string Card::author_url() const
{
    if (_tree["author_url"].isString())
    {
        return _tree["author_url"].asString();
    }

    ttdebug << "Could not get attachment data: author_url\n";
    return "";
}

const string Card::description() const
{
    if (_tree["description"].isString())
    {
        return _tree["description"].asString();
    }

    ttdebug << "Could not get attachment data: description\n";
    return "";
}

const uint64_t Card::height() const
{
    if (_tree["height"].isUInt64())
    {
        return _tree["height"].asUInt64();
    }

    ttdebug << "Could not get attachment data: height\n";
    return 0;
}

const string Card::html() const
{
    if (_tree["html"].isString())
    {
        return _tree["html"].asString();
    }

    ttdebug << "Could not get attachment data: html\n";
    return "";
}

const string Card::image() const
{
    if (_tree["image"].isString())
    {
        return _tree["image"].asString();
    }

    ttdebug << "Could not get attachment data: image\n";
    return "";
}

const string Card::provider_name() const
{
    if (_tree["provider_name"].isString())
    {
        return _tree["provider_name"].asString();
    }

    ttdebug << "Could not get attachment data: provider_name\n";
    return "";
}

const string Card::provider_url() const
{
    if (_tree["provider_url"].isString())
    {
        return _tree["provider_url"].asString();
    }

    ttdebug << "Could not get attachment data: provider_url\n";
    return "";
}

const string Card::title() const
{
    if (_tree["title"].isString())
    {
        return _tree["title"].asString();
    }

    ttdebug << "Could not get attachment data: title\n";
    return "";
}

const Easy::card_type Card::type() const
{
    const string strtype = _tree["type"].asString();
        if (strtype.compare("link"))
            return card_type::link;
        else if (strtype.compare("photo"))
            return card_type::photo;
        else if (strtype.compare("video"))
            return card_type::video;
        else if (strtype.compare("rich"))
            return card_type::rich;

    ttdebug << "Could not get account data: type\n";
    return card_type::unknown;
}

const string Card::url() const
{
    if (_tree["url"].isString())
    {
        return _tree["url"].asString();
    }

    ttdebug << "Could not get attachment data: url\n";
    return "";
}

const uint64_t Card::width() const
{
    if (_tree["width"].isUInt64())
    {
        return _tree["width"].asUInt64();
    }

    ttdebug << "Could not get attachment data: width\n";
    return 0;
}
