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

#include <array>
#include <algorithm>
#include "account.hpp"
#include "debug.hpp"

using namespace Mastodon;
using Account = Easy::Account;

bool Account::valid() const
{
    const std::vector<string> attributes =
    {{
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
        "header_static"
    }};

    return Entity::check_valid(attributes);
}

const string Account::acct() const
{
    return get_string("acct");
}

const string Account::avatar() const
{
    return get_string("avatar");
}

Account Account::avatar(const string &avatar)
{
    set("avatar", Json::Value(avatar));
    return *this;
}

const string Account::avatar_static() const
{
    return get_string("avatar_static");
}

bool Account::bot() const
{
    return get_bool("bot");
}

const Easy::time Account::created_at() const
{
    return get_time("created_at");
}

const string Account::display_name() const
{
    return get_string("display_name");
}

Account Account::display_name(const string &display_name)
{
    set("display_name", Json::Value(display_name));
    return *this;
}

const std::vector<Account::fields_pair> Account::fields() const
{
    const Json::Value &node = get("fields");

    if (node.isArray())
    {
        std::vector<Account::fields_pair> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           {
                               return Account::fields_pair
                                   (value["name"].asString(),
                                    value["value"].asString());
                           });
        return vec;
    }

    return {};
}

Account Account::fields(std::vector<Account::fields_pair> &fields)
{
    Json::Value jsonarray(Json::arrayValue);

    for (const fields_pair &field : fields)
    {
        Json::Value jsonkeyval(Json::objectValue);
        jsonkeyval["name"] = field.first;
        jsonkeyval["value"] = field.second;
        jsonarray.append(jsonkeyval);
    }
    set("fields", jsonarray);
    return *this;
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

Account Account::header(const string &header)
{
    set("header", Json::Value(header));
    return *this;
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

Account Account::locked(const bool &locked)
{
    set("locked", Json::Value(locked));
    return *this;
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
        // TODO: Find an account with moved-node and test
        return Account(get("moved").toStyledString());
    }

    return Account();
}

const string Account::note() const
{
    return get_string("note");
}

Account Account::note(const string &note)
{
    set("note", Json::Value(note));
    return *this;
}

Easy::visibility_type Account::privacy() const
{
    const string strprivacy = get_string("source.privacy");
    if (strprivacy.compare("public") == 0)
        return visibility_type::Public;
    else if (strprivacy.compare("unlisted") == 0)
        return visibility_type::Unlisted;
    else if (strprivacy.compare("private") == 0)
        return visibility_type::Private;
    else if (strprivacy.compare("direct") == 0)
        return visibility_type::Direct;

    ttdebug << "Could not get data: source.privacy\n";
    return visibility_type::Undefined;
}

bool Account::sensitive() const
{
    return get_bool("source.sensitive");
}

bool Account::Source::valid() const
{
    return true;
}

const std::vector<Account::fields_pair> Account::Source::fields() const
{
    const Json::Value &node = get("fields");

    if (node.isArray())
    {
        std::vector<Account::fields_pair> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           {
                               return Account::fields_pair
                                   (value["name"].asString(),
                                    value["value"].asString());
                           });
        return vec;
    }

    return {};
}

Account::Source Account::Source::fields
    (std::vector<Account::fields_pair> &fields)
{
    Json::Value jsonarray(Json::arrayValue);

    for (const fields_pair &field : fields)
    {
        Json::Value jsonkeyval(Json::objectValue);
        jsonkeyval["name"] = field.first;
        jsonkeyval["value"] = field.second;
        jsonarray.append(jsonkeyval);
    }
    set("fields", jsonarray);
    return *this;
}

const string Account::Source::note() const
{
    return get_string("note");
}

Account::Source Account::Source::note(const string &note)
{
    set("note", Json::Value(note));
    return *this;
}

Easy::visibility_type Account::Source::privacy() const
{
    const string strprivacy = get_string("privacy");
    if (strprivacy.compare("public") == 0)
        return visibility_type::Public;
    else if (strprivacy.compare("unlisted") == 0)
        return visibility_type::Unlisted;
    else if (strprivacy.compare("private") == 0)
        return visibility_type::Private;
    else if (strprivacy.compare("direct") == 0)
        return visibility_type::Direct;

    ttdebug << "Could not get data: source.privacy\n";
    return visibility_type::Undefined;
}

Account::Source Account::Source::privacy(const Easy::visibility_type &privacy)
{
    string strprivacy = "";
    switch (privacy)
    {
        case visibility_type::Public:
        {
            strprivacy = "public";
            break;
        }
        case visibility_type::Unlisted:
        {
            strprivacy = "unlisted";
            break;
        }
        case visibility_type::Private:
        {
            strprivacy = "private";
            break;
        }
        case visibility_type::Direct:
        {
            strprivacy = "direct";
            break;
        }
        default:
        {
            strprivacy = "undefined";
            break;
        }
    }
    set("privacy", Json::Value(strprivacy));
    return *this;
}

bool Account::Source::sensitive() const
{
    return get_bool("sensitive");
}

Account::Source Account::Source::sensitive(const bool &sensitive)
{
    set("source", Json::Value(sensitive));
    return *this;
}

const Account::Source Account::source() const
{
    return Account::Source(get("source"));
}

Account Account::source(const Account::Source &source)
{
    set("source", Json::Value(source.to_object()));
    return *this;
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
