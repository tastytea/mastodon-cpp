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
#include "debug.hpp"

using namespace Mastodon;
using Attachment = Easy::Attachment;

Attachment::Attachment(const string &json)
: Entity(json)
{}

Attachment::Attachment()
: Entity()
{}

bool Attachment::valid() const
{
    const std::vector<string> attributes =
    {{
        "id",
        "type",
        "url",
        "preview_url"
    }};

    return Entity::check_valid(attributes);
}

double Attachment::aspect() const
{
    return get_double("meta.original.aspect");
}

double Attachment::aspect_small() const
{
    return get_double("meta.small.aspect");
}

uint64_t Attachment::bitrate() const
{
    return get_uint64("meta.original.bitrate");
}

const string Attachment::description() const
{
    return get_string("description");
}

Attachment Attachment::description(const string &description)
{
    set("description", Json::Value(description));
    return *this;
}

const std::chrono::duration<double> Attachment::duration() const
{
    const double sec = get_double("meta.original.duration");

    return std::chrono::duration<double>(sec);
}

const string Attachment::file() const
{
    return get_string("file");
}

Attachment Attachment::file(const string &file)
{
    set("file", Json::Value(file));
    return *this;
}


const std::array<double, 2> Attachment::focus() const
{
    const Json::Value x = get("meta.focus.x");
    const Json::Value y = get("meta.focus.y");
    if (x.isDouble() && y.isDouble())
    {
        return
        {{
            x.asDouble(),
            y.asDouble()
        }};
    }

    return {};
}

Attachment Attachment::focus(const std::array<double, 2> &focus)
{
    set("meta.focus.x", Json::Value(focus[0]));
    set("meta.focus.y", Json::Value(focus[1]));
    return *this;
}

double Attachment::framerate() const
{
    string strframes = get_string("meta.original.frame_rate");

    if (!strframes.empty())
    {
        std::size_t pos = strframes.find('/');
        if (pos != std::string::npos)
        {
            std::uint16_t frames = std::stoul(strframes.substr(0, pos));
            std::uint16_t divider = std::stoul(strframes.substr(pos + 1));

            return frames / divider;
        }
    }

    return 0.0;
}

uint64_t Attachment::height() const
{
    return get_uint64("meta.original.height");
}

uint64_t Attachment::height_small() const
{
    return get_uint64("meta.small.height");
}

const string Attachment::id() const
{
    return get_string("id");
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

Easy::attachment_type Attachment::type() const
{
    const string strtype = get_string("type");
    if (strtype.compare("image") == 0)
        return attachment_type::Image;
    else if (strtype.compare("video") == 0)
        return attachment_type::Video;
    else if (strtype.compare("gifv") == 0)
        return attachment_type::Gifv;
    else if (strtype.compare("unknown") == 0)
        return attachment_type::Unknown;

    ttdebug << "Could not get data: type\n";
    return attachment_type::Undefined;
}

const string Attachment::url() const
{
    return get_string("url");
}

uint64_t Attachment::width() const
{
    return get_uint64("meta.original.width");
}

uint64_t Attachment::width_small() const
{
    return get_uint64("meta.small.width");
}
