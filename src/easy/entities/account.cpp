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

#include "account.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Account = Easy::Account;

Account::Account(const string &json)
: Entity(json)
{}

Account::Account()
: Entity()
{}

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

const system_clock::time_point Account::created_at() const
{
    return get_time_point("created_at");
}

const string Account::display_name() const
{
    return get_string("display_name");
}

const std::uint_fast64_t Account::followers_count() const
{
    return get_uint64("followers_count");
}

const std::uint_fast64_t Account::following_count() const
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

const std::uint_fast64_t Account::id() const
{
    return std::stoull(get_string("id"));
}

const bool Account::locked() const
{
    return get_bool("locked");
}

const bool Account::has_moved() const
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
    return get_string("source.note");
}

const string Account::note_plain() const
{
    return get_string("source.note");
}

const Easy::visibility_type Account::privacy() const
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

const bool Account::sensitive() const
{
    return get_bool("source.sensitive");
}

const std::uint_fast64_t Account::statuses_count() const
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