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

#include <sstream>
#include "attachment.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Attachment = Easy::Attachment;

Attachment::Attachment(const string &json)
: Entity(json)
{}

Attachment::Attachment()
: Entity()
{}

const double Attachment::aspect() const
{
    return get_double("meta.original.aspect");
}

const double Attachment::aspect_small() const
{
    return get_double("meta.small.aspect");
}

const string Attachment::description() const
{
    return get_string("description");
}

const std::array<uint64_t, 2> Attachment::focus() const
{
    const Json::Value x = get("meta.focus.x");
    const Json::Value y = get("meta.focus.y");
    if (x.isUInt64() && y.isUInt64())
    {
        return
        {{
            x.asUInt64(),
            y.asUInt64()
        }};
    }

    return {};
}

const uint64_t Attachment::height() const
{
    return get_uint64("meta.original.height");
}

const uint64_t Attachment::height_small() const
{
    return get_uint64("meta.small.height");
}

const std::uint64_t Attachment::id() const
{
    return std::stoull(get_string("id"));
}

const string Attachment::preview_url() const
{
    return get_string("preview_url");
}

const string Attachment::remote_url() const
{
    return get_string("remote_url");
}

const string Attachment::size() const
{
    return get_string("meta.original.size");
}

const string Attachment::size_small() const
{
    return get_string("meta.small.size");
}

const string Attachment::text_url() const
{
    return get_string("text_url");
}

const Easy::attachment_type Attachment::type() const
{
    const string strtype = get_string("type");
    if (strtype.compare("image") == 0)
        return attachment_type::image;
    else if (strtype.compare("video") == 0)
        return attachment_type::video;
    else if (strtype.compare("gifv") == 0)
        return attachment_type::gifv;
    else if (strtype.compare("unknown") == 0)
        return attachment_type::unknown;

    ttdebug << "Could not get data: type\n";
    return attachment_type::unknown;
}

const string Attachment::url() const
{
    return get_string("url");
}

const uint64_t Attachment::width() const
{
    return get_uint64("meta.original.width");
}

const uint64_t Attachment::width_small() const
{
    return get_uint64("meta.small.width");
}
