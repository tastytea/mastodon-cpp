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
#include <cstdint>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>  // get_time
#include <sstream>
#include <jsoncpp/json/json.h>
#include "account.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Account = Easy::Account;
using std::string;
using std::uint64_t;

Account::Account(const string &json)
: Entity(json)
{
    //
}

const string Account::acct() const
{
    if (_tree["acct"].isString())
    {
        return _tree["acct"].asString();
    }

    ttdebug << "Could not get account data: acct\n";
    return "";
}

const string Account::avatar() const
{
    if (_tree["avatar"].isString())
    {
        return _tree["avatar"].asString();
    }

    ttdebug << "Could not get account data: avatar\n";
    return "";
}

const string Account::avatar_static() const
{
    if (_tree["avatar_static"].isString())
    {
        return _tree["avatar_static"].asString();
    }

    ttdebug << "Could not get account data: avatar_static\n";
    return "";
}

const std::chrono::system_clock::time_point Account::created_at() const
{
    if (_tree["created_at"].isString())
    {
        std::stringstream sstime(_tree["created_at"].asString());
        struct std::tm tm = {0};
        sstime >> std::get_time(&tm, "%Y-%m-%dT%T");
        std::time_t time = timegm(&tm);
        return std::chrono::system_clock::from_time_t(time);
    }

    ttdebug << "Could not get account data: created_at\n";
    // Return clocks epoch
    return std::chrono::system_clock::time_point();
}

const string Account::display_name() const
{
    if (_tree["display_name"].isString())
    {
        return _tree["display_name"].asString();
    }

    ttdebug << "Could not get account data: display_name\n";
    return "";
}

const std::uint64_t Account::followers_count() const
{
    if (_tree["followers_count"].isUInt64())
    {
        return _tree["followers_count"].asUInt64();
    }

    ttdebug << "Could not get account data: followers_count\n";
    return 0;
}

const std::uint64_t Account::following_count() const
{
    if (_tree["following_count"].isUInt64())
    {
        return _tree["following_count"].asUInt64();
    }

    ttdebug << "Could not get account data: following_count\n";
    return 0;
}

const string Account::header() const
{
    if (_tree["header"].isString())
    {
        return _tree["header"].asString();
    }

    ttdebug << "Could not get account data: header\n";
    return "";
}

const string Account::header_static() const
{
    if (_tree["header_static"].isString())
    {
        return _tree["header_static"].asString();
    }

    ttdebug << "Could not get account data: header_static\n";
    return "";
}

const std::uint64_t Account::id() const
{
    if (_tree["id"].isUInt64())
    {
        return _tree["id"].asUInt64();
    }

    ttdebug << "Could not get account data: id\n";
    return 0;
}

const bool Account::locked() const
{
    if (_tree["locked"].isBool())
    {
        return _tree["locked"].asBool();
    }

    ttdebug << "Could not get account data: locked\n";
    return false;
}

const bool Account::has_moved() const
{
    if (_tree["moved"].isObject())
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
        return Account(_tree["moved"].toStyledString());
    }

    ttdebug << "Could not get account data: moved\n";
    return Account("");
}

const string Account::note() const
{
    if (_tree["note"].isString())
    {
        return _tree["note"].asString();
    }

    ttdebug << "Could not get account data: note\n";
    return "";
}

const string Account::note_plain() const
{
    if (_tree["source"]["note"].isString())
    {
        return _tree["source"]["note"].asString();
    }

    ttdebug << "Could not get account data: note_plain\n";
    return "";
}

const Easy::visibility Account::privacy() const
{
    if (_tree["source"]["privacy"].isString())
    {
        const string strprivacy = _tree["source"]["privacy"].asString();
        if (strprivacy.compare("public"))
            return visibility::Public;
        else if (strprivacy.compare("unlisted"))
            return visibility::Unlisted;
        else if (strprivacy.compare("private"))
            return visibility::Private;
        else if (strprivacy.compare("direct"))
            return visibility::Direct;
    }

    ttdebug << "Could not get account data: privacy\n";
    return visibility::Undefined;
}

const bool Account::sensitive() const
{
    if (_tree["source"]["sensitive"].isBool())
    {
        return _tree["source"]["sensitive"].asBool();
    }

    ttdebug << "Could not get account data: sensitive\n";
    return false;
}

const std::uint64_t Account::statuses_count() const
{
    if (_tree["statuses_count"].isUInt64())
    {
        return _tree["statuses_count"].asUInt64();
    }

    ttdebug << "Could not get account data: statuses_count\n";
    return 0;
}

const string Account::username() const
{
    if (_tree["username"].isString())
    {
        return _tree["username"].asString();
    }

    ttdebug << "Could not get account data: username\n";
    return "";
}
