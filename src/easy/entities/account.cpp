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

#include <algorithm>
#include "account.hpp"
#include "debug.hpp"
#include "easy/easy.hpp"

using namespace Mastodon;
using Account = Easy::Account;

bool Account::valid() const
{
    return Entity::check_valid(
        {
            "id",
            "username",
            "acct",
            "display_name",
            "locked",
            "created_at",
            "followers_count",
            "following_count",
            "statuses_count",
            "note",
            "url",
            "avatar",
            "avatar_static",
            "header",
            "header_static",
            "emojis"
        });
}

const string Account::acct() const
{
    return get_string("acct");
}

const string Account::avatar() const
{
    return get_string("avatar");
}

const string Account::avatar_static() const
{
    return get_string("avatar_static");
}

bool Account::bot() const
{
    return get_bool("bot");
}

const Easy::time_type Account::created_at() const
{
    return get_time("created_at");
}

const string Account::display_name() const
{
    return get_string("display_name");
}

const std::vector<Easy::Emoji> Account::emojis()
{
    const Json::Value &node = get("emojis");

    if (node.isArray())
    {
        std::vector<Easy::Emoji> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                       {
                           return Easy::Emoji(value);
                       });
        return vec;
    }

    return {};
}

const vector<Easy::account_field_type> Account::fields() const
{
    const Json::Value &node = get("fields");

    if (node.isArray())
    {
        vector<Easy::account_field_type> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                       {
                           return Easy::account_field_type(
                               {
                                   value["name"].asString(),
                                   value["value"].asString(),
                                   Easy::string_to_time(
                                       value["verified_at"].asString())
                               });
                       });
        return vec;
    }

    return {};
}

std::uint64_t Account::followers_count() const
{
    return get_uint64("followers_count");
}

std::uint64_t Account::following_count() const
{
    return get_uint64("following_count");
}

const string Account::header() const
{
    return get_string("header");
}

const string Account::header_static() const
{
    return get_string("header_static");
}

const string Account::id() const
{
    return get_string("id");
}

bool Account::locked() const
{
    return get_bool("locked");
}

bool Account::has_moved() const
{
    if (get("moved").isObject())
    {
        return true;
    }

    return false;
}

const Account Account::moved() const
{
    if (has_moved())
    {
        return Account(get("moved"));
    }

    return Account();
}

const string Account::note() const
{
    return get_string("note");
}

Easy::visibility_type Account::privacy() const
{
    const string strprivacy = get_string("privacy");
    if (strprivacy == "public")
        return visibility_type::Public;
    else if (strprivacy == "unlisted")
        return visibility_type::Unlisted;
    else if (strprivacy == "private")
        return visibility_type::Private;
    else if (strprivacy == "direct")
        return visibility_type::Direct;

    return visibility_type::Undefined;
}

bool Account::sensitive() const
{
    return get_bool("source.sensitive");
}

const Account::Source Account::source() const
{
    return Account::Source(get("source"));
}

std::uint64_t Account::statuses_count() const
{
    return get_uint64("statuses_count");
}

const string Account::url() const
{
    return get_string("url");
}

const string Account::username() const
{
    return get_string("username");
}

bool Account::Source::valid() const
{
    return Entity::check_valid(
        {
            "note",
            "fields"
        });
}

const vector<Easy::account_field_type> Account::Source::fields() const
{
    const Json::Value &node = get("fields");

    if (node.isArray())
    {
        vector<Easy::account_field_type> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                       {
                           return Easy::account_field_type(
                               {
                                   value["name"].asString(),
                                   value["value"].asString(),
                                   Easy::string_to_time(
                                       value["verified_at"].asString())
                               });
                           });
        return vec;
    }

    return {};
}

const string Account::Source::language() const
{
    return get_string("language");
}

const string Account::Source::note() const
{
    return get_string("note");
}

Easy::visibility_type Account::Source::privacy() const
{
    const string strprivacy = get_string("privacy");
    if (strprivacy == "public")
        return visibility_type::Public;
    else if (strprivacy == "unlisted")
        return visibility_type::Unlisted;
    else if (strprivacy == "private")
        return visibility_type::Private;
    else if (strprivacy == "direct")
        return visibility_type::Direct;

    return visibility_type::Undefined;
}

bool Account::Source::sensitive() const
{
    return get_bool("sensitive");
}
