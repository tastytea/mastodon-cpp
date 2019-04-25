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

#include <iostream>
#include <algorithm>
#include <jsoncpp/json/json.h>
#include "status.hpp"

using namespace Mastodon;
using Status = Easy::Status;

bool Status::valid() const
{
    return Entity::check_valid(
        {
            "id",
            "uri",
            "account",
            "content",
            "created_at",
            "emojis",
            "replies_count",
            "reblogs_count",
            "favourites_count",
            "sensitive",
            "spoiler_text",
            "visibility",
            "media_attachments",
            "mentions",
            "tags",
            "application"
        });
}

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

const Easy::Card Status::card() const
{
    const Json::Value node = get("card");
    if (node.isObject())
    {
        return Easy::Card(node.toStyledString());
    }

    return Easy::Card();
}

const Easy::time Status::created_at() const
{
    return get_time("created_at");
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
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           { return Easy::Emoji(value); });
        return vec;
    }

    return {};
}

bool Status::favourited() const
{
    return get_bool("favourited");
}

uint64_t Status::favourites_count() const
{
    return get_uint64("favourites_count");
}

const string Status::id() const
{
    return get_string("id");
}

const string Status::in_reply_to_id() const
{
    return get_string("in_reply_to_id");
}

Status Status::in_reply_to_id(const string &in_reply_to_id)
{
    set("in_reply_to_id", Json::Value(in_reply_to_id));
    return *this;
}

const string Status::in_reply_to_account_id() const
{
    return get_string("in_reply_to_account_id");
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
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           { return Easy::Attachment(value); });
        return vec;
    }

    return {};
}

Status Status::media_attachments
    (const std::vector<Attachment> &media_attachments)
{
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
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           { return Easy::Mention(value); });
        return vec;
    }

    return {};
}

bool Status::muted() const
{
    return get_bool("muted");
}

bool Status::pinned() const
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

bool Status::reblogged() const
{
    return get_bool("reblogged");
}

uint64_t Status::reblogs_count() const
{
    return get_uint64("reblogs_count");
}

uint64_t Status::replies_count() const
{
    return get_uint64("replies_count");
}

bool Status::sensitive() const
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
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           { return Easy::Tag(value); });
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

Easy::visibility_type Status::visibility() const
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
