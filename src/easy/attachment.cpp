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
#include "easy.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Attachment = Easy::Attachment;
using std::string;

Attachment::Attachment(const string &json)
{
    std::stringstream ss(json);
    ss >> _tree;

    if (_tree.isNull())
    {
        std::cerr << "ERROR: Could not build Attachment from JSON string\n";
        ttdebug << "String was: " << json << '\n';
    }
    else
    {
        _valid = true;
    }
}

const bool Attachment::valid() const
{
    return _valid;
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
