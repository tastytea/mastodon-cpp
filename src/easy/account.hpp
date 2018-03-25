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

#ifndef MASTODON_CPP_EASY_ACCOUNT_HPP
#define MASTODON_CPP_EASY_ACCOUNT_HPP

#include <string>
#include <cstdint>
#include <chrono>
#include <jsoncpp/json/json.h>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy.hpp>
#endif

using std::string;
using std::uint16_t;
using std::uint64_t;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold accounts.
     */
    class Easy::Account : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs an Account object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Account(const string &json);

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
        const uint64_t followers_count() const;

        /*!
         *  @brief  Returns number of people this account follows
         */
        const uint64_t following_count() const;

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
        const uint64_t id() const;

        /*!
         *  @brief  Returns true if the account is locked
         */
        const bool locked() const;

        /*!
         *  @brief  Returns true if the account has been moved
         */
        const bool has_moved() const;

        /*!
         *  @brief  If the owner decided to switch accounts, new account is in
         *          this attribute
         */
        const Account moved() const;

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
         *  @brief  Returns if media is marked as sensitive by default
         */
        const bool sensitive() const;

        /*!
         *  @brief  Returns number of statuses
         */
        const uint64_t statuses_count() const;

        /*!
         *  @brief  Returns URL of the profile
         */
        const string url() const;

        /*!
         *  @brief  Returns username (without @hostname)
         */
        const string username() const;
};
}

#endif  // MASTODON_CPP_EASY_ACCOUNT_HPP
