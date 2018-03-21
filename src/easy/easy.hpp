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

#ifndef MASTODON_EASY_CPP_HPP
#define MASTODON_EASY_CPP_HPP

#include <string>
#include <cstdint>
#include <chrono>
#include <jsoncpp/json/json.h>
#include "mastodon-cpp/mastodon-cpp.hpp"

using std::string;
using std::uint16_t;

namespace Mastodon
{
/*!
 *  @brief  Child of Mastodon::API with abstract methods.
 */
class Easy : public API
{
public:
    /*!
     *  @brief  Describes visibility of toots.
     *  
     *          The names begin with a capital letter because some of them
     *          are reserved keywords when written in all-lowercase.
     */
    enum class visibility
    {
        Direct,
        Private,
        Unlisted,
        Public,
        Undefined
    };

    /*!
     *  @brief  Constructs a new Easy object.
     *  
     *          To register your application, leave access_token blank and call
     *          register_app1() and register_app2().
     *
     *  @param  instance      The hostname of your instance
     *  @param  access_token  The access token
     */
    explicit Easy(const string &instance, const string &access_token);

    /*!
     *  @brief  Class to hold accounts.
     */
    class Account
    {
    public:
        /*!
         *  @brief  Constructs an account object from a JSON string.
         *
         *  @param  json    JSON string
         */
        Account(const string &json);

        /*!
         *  @brief  Returns true if the account holds valid data
         */
        const bool valid() const;

        /*!
         *  @brief  Returns username
         *
         *          `username` for users on the same instance, `user@hostname`
         *          for users on other instances.
         */
        const string acct() const;

        /*!
         *  @brief  Returns URL of avatar
         */
        const string avatar() const;

        /*!
         *  @brief  Returns URL of static avatar
         */
        const string avatar_static() const;

        /*!
         *  @brief  Returns time of creation
         */
        const std::chrono::system_clock::time_point created_at() const;

        /*!
         *  @brief  Returns display name
         */
        const string display_name() const;

        /*!
         *  @brief  Returns number of followers
         */
        const std::uint64_t followers_count() const;

        /*!
         *  @brief  Returns number of people this account follows
         */
        const std::uint64_t following_count() const;

        /*!
         *  @brief  Returns URL of header image
         */
        const string header() const;

        /*!
         *  @brief  Returns URL of static header image
         */
        const string header_static() const;

        /*!
         *  @brief  Returns account-ID
         */
        const std::uint64_t id() const;

        /*!
         *  @brief  Returns true if the account is locked
         */
        const bool locked() const;

        /*!
         *  @brief  Returns note
         */
        const string note() const;

        /*!
         *  @brief  Returns plaintext version of note
         */
        const string note_plain() const;

        /*!
         *  @brief  Returns default privacy of new toots
         */
        const visibility privacy() const;

        /*!
         *  @brief  Returns if media is amrked as sensitive by default
         */
        const bool sensitive() const;

        /*!
         *  @brief  Returns number of statuses
         */
        const std::uint64_t statuses_count() const;

        /*!
         *  @brief  Returns URL of the profile
         */
        const string url() const;

        /*!
         *  @brief  Returns username (without @hostname)
         */
        const string username() const;

    private:
        Json::Value _tree;
        bool _valid;
    };
};
}

#endif  // MASTODON_EASY_CPP_HPP
