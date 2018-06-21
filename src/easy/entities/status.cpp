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

#include <iostream>
#include <jsoncpp/json/json.h>
#include "status.hpp"

using namespace Mastodon;
using Status = Easy::Status;

Status::Status(const string &json)
: Entity(json)
{}

Status::Status()
: Entity()
{}

const Easy::Account Status::account() const
{
    const Json::Value node = get("account");
    if (node.isObject())
    {
        return Easy::Account(node.toStyledString());
    }

    return Easy::Account();
}

const Easy::Application Status::application() const
{
    const Json::Value node = get("application");
    if (node.isObject())
    {
        return Easy::Application(node.toStyledString());
    }

    return Easy::Application();
}

const system_clock::time_point Status::created_at() const
{
    return get_time_point("created_at");
}

const string Status::content() const
{
    return get_string("content");
}

Status Status::content(const string &content)
{
    set("content", Json::Value(content));
    return *this;
}

const std::vector<Easy::Emoji> Status::emojis() const
{
    const Json::Value node = get("emojis");
    if (node.isArray())
    {
        std::vector<Easy::Emoji> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(Easy::Emoji(value.toStyledString()));
        }
        return vec;
    }

    return {};
}

const bool Status::favourited() const
{
    return get_bool("favourited");
}

const uint_fast64_t Status::favourites_count() const
{
    return get_uint64("favourites_count");
}

const uint_fast64_t Status::id() const
{
    return stouint64(get_string("id"));
}

const uint_fast64_t Status::in_reply_to_id() const
{
    return stouint64(get_string("in_reply_to_id"));
}

Status Status::in_reply_to_id(const uint_fast64_t &in_reply_to_id)
{
    set("in_reply_to_id", Json::Value(std::to_string(in_reply_to_id)));
    return *this;
}

const uint_fast64_t Status::in_reply_to_account_id() const
{
    return stouint64(get_string("in_reply_to_account_id"));
}

const string Status::language() const
{
    return get_string("language");
}

Status Status::language(const string &language)
{
    set("language", Json::Value(language));
    return *this;
}

const std::vector<Easy::Attachment> Status::media_attachments() const
{
    const Json::Value node = get("media_attachments");
    if (node.isArray())
    {
        std::vector<Easy::Attachment> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(Easy::Attachment(value.toStyledString()));
        }
        return vec;
    }

    return {};
}

Status Status::media_attachments
    (const std::vector<Attachment> &media_attachments)
{
    // FIXME: Needs writable Easy::Attachment()
    Json::Value jsonarray(Json::arrayValue);

    for (const Attachment &att : media_attachments)
    {
        jsonarray.append(att.to_object());
    }
    set("media_attachments", jsonarray);
    return *this;
}

const std::vector<Easy::Mention> Status::mentions() const
{
    const Json::Value node = get("mentions");
    if (node.isArray())
    {
        std::vector<Easy::Mention> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(Easy::Mention(value.toStyledString()));
        }
        return vec;
    }

    return {};
}

const bool Status::muted() const
{
    return get_bool("muted");
}

const bool Status::pinned() const
{
    return get_bool("pinned");
}

const Status Status::reblog() const
{
    const Json::Value node = get("reblog");
    if (node.isObject())
    {
        return Easy::Status(node.toStyledString());
    }

    return Easy::Status();
}

const bool Status::reblogged() const
{
    return get_bool("reblogged");
}

const uint_fast64_t Status::reblogs_count() const
{
    return get_uint64("reblogs_count");
}

const bool Status::sensitive() const
{
    return get_bool("sensitive");
}

Status Status::sensitive(const bool &sensitive)
{
    set("sensitive", Json::Value(sensitive));
    return *this;
}

const string Status::spoiler_text() const
{
    return get_string("spoiler_text");
}

Status Status::spoiler_text(const string &spoiler_text)
{
    set("spoiler_text", Json::Value(spoiler_text));
    return *this;
}

const std::vector<Easy::Tag> Status::tags() const
{
    const Json::Value node = get("tags");
    if (node.isArray())
    {
        std::vector<Easy::Tag> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(Easy::Tag(value.toStyledString()));
        }
        return vec;
    }

    return {};
}

const string Status::uri() const
{
    return get_string("uri");
}

const string Status::url() const
{
    return get_string("url");
}

const Easy::visibility_type Status::visibility() const
{
    const string strvisibility = get_string("visibility");
    if (strvisibility.compare("public") == 0)
        return visibility_type::Public;
    else if (strvisibility.compare("unlisted") == 0)
        return visibility_type::Unlisted;
    else if (strvisibility.compare("private") == 0)
        return visibility_type::Private;
    else if (strvisibility.compare("direct") == 0)
        return visibility_type::Direct;

    return visibility_type::Undefined;
}

Status Status::visibility(const visibility_type &visibility)
{
    switch (visibility)
    {
        case visibility_type::Direct:
            set("visibility", "direct");
            break;
        case visibility_type::Private:
            set("visibility", "private");
            break;
        case visibility_type::Unlisted:
            set("visibility", "unlisted");
            break;
        case visibility_type::Public:
            set("visibility", "public");
            break;
        default:
            std::cerr << "WARNING: setting visibility to Undefined "
                         "has no effect.\n";
            break;
    };
    return *this;
}
