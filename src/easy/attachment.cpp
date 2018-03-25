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
#include <array>
#include <jsoncpp/json/json.h>
#include "attachment.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Attachment = Easy::Attachment;
using std::string;
using std::uint64_t;

Attachment::Attachment(const string &json)
: Entity(json)
{
    //
}

const double Attachment::aspect() const
{
    if (_tree["meta"]["original"]["aspect"].isDouble())
    {
        return _tree["meta"]["original"]["aspect"].asDouble();
    }

    ttdebug << "Could not get attachment data: aspect\n";
    return 0;
}

const double Attachment::aspect_small() const
{
    if (_tree["meta"]["small"]["aspect"].isDouble())
    {
        return _tree["meta"]["small"]["aspect"].asDouble();
    }

    ttdebug << "Could not get attachment data: aspect_small\n";
    return 0;
}

const string Attachment::description() const
{
    if (_tree["description"].isString())
    {
        return _tree["description"].asString();
    }

    ttdebug << "Could not get attachment data: description\n";
    return "";
}

const std::array<uint64_t, 2> Attachment::focus() const
{
    if (_tree["meta"]["focus"]["x"].isUInt64())
    {
        return
        {{
            _tree["meta"]["focus"]["x"].asUInt64(),
            _tree["meta"]["focus"]["y"].asUInt64()
        }};
    }

    ttdebug << "Could not get attachment data: focus\n";
    return {};
}

const uint64_t Attachment::height() const
{
    if (_tree["meta"]["original"]["height"].isDouble())
    {
        return _tree["meta"]["original"]["height"].asDouble();
    }

    ttdebug << "Could not get attachment data: height\n";
    return 0;
}

const uint64_t Attachment::height_small() const
{
    if (_tree["meta"]["small"]["height"].isDouble())
    {
        return _tree["meta"]["small"]["height"].asDouble();
    }

    ttdebug << "Could not get attachment data: height_small\n";
    return 0;
}

const std::uint64_t Attachment::id() const
{
    if (_tree["id"].isUInt64())
    {
        return _tree["id"].asUInt64();
    }

    ttdebug << "Could not get attachment data: id\n";
    return 0;
}

const string Attachment::preview_url() const
{
    if (_tree["preview_url"].isString())
    {
        return _tree["preview_url"].asString();
    }

    ttdebug << "Could not get attachment data: preview_url\n";
    return "";
}

const string Attachment::remote_url() const
{
    if (_tree["remote_url"].isString())
    {
        return _tree["remote_url"].asString();
    }

    ttdebug << "Could not get attachment data: remote_url\n";
    return "";
}

const string Attachment::size() const
{
    if (_tree["meta"]["original"]["size"].isString())
    {
        return _tree["meta"]["original"]["size"].asString();
    }

    ttdebug << "Could not get attachment data: size\n";
    return "";
}

const string Attachment::size_small() const
{
    if (_tree["meta"]["original"]["size"].isString())
    {
        return _tree["meta"]["original"]["size"].asString();
    }

    ttdebug << "Could not get attachment data: size_small\n";
    return "";
}

const string Attachment::text_url() const
{
    if (_tree["text_url"].isString())
    {
        return _tree["text_url"].asString();
    }

    ttdebug << "Could not get attachment data: text_url\n";
    return "";
}

const Easy::attachment_type Attachment::type() const
{
    const string strtype = _tree["type"].asString();
        if (strtype.compare("image"))
            return attachment_type::image;
        else if (strtype.compare("video"))
            return attachment_type::video;
        else if (strtype.compare("gifv"))
            return attachment_type::gifv;
        else if (strtype.compare("unknown"))
            return attachment_type::unknown;

    ttdebug << "Could not get account data: type\n";
    return attachment_type::unknown;
}

const string Attachment::url() const
{
    if (_tree["url"].isString())
    {
        return _tree["url"].asString();
    }

    ttdebug << "Could not get attachment data: url\n";
    return "";
}

const uint64_t Attachment::width() const
{
    if (_tree["meta"]["original"]["width"].isDouble())
    {
        return _tree["meta"]["original"]["width"].asDouble();
    }

    ttdebug << "Could not get attachment data: width\n";
    return 0;
}

const uint64_t Attachment::width_small() const
{
    if (_tree["meta"]["small"]["width"].isDouble())
    {
        return _tree["meta"]["small"]["width"].asDouble();
    }

    ttdebug << "Could not get attachment data: width_small\n";
    return 0;
}
