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
#include <vector>
#include <utility>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/easy.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/easy.hpp>
#endif

using std::string;
using std::uint_fast64_t;
using std::chrono::system_clock;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold accounts.
     *  
     *  @since before 0.11.0
     */
    class Easy::Account : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Describes a field. Format: name, value
         *
         *  @since  0.16.1
         */
        using fields_pair = std::pair<const string, const string>;

        /*!
         *  @brief  Constructs an Account object from a JSON string.
         *
         *  @param  json    JSON string
         *  
         *  @since before 0.11.0
         */
        explicit Account(const string &json);

        /*!
         *  @brief  Constructs an empty Account object.
         *  
         *  @since before 0.11.0
         */
        Account();

        virtual bool valid() const;

        /*!
         *  @brief  Returns username
         *
         *          `username` for users on the same instance, `user@hostname`
         *          for users on other instances.
         *  
         *  @since before 0.11.0
         */
        const string acct() const;

        /*!
         *  @brief  Returns URL of avatar
         *  
         *  @since before 0.11.0
         */
        const string avatar() const;

        /*!
         *  @brief  Sets avatar
         *  
         *          Filename or base64-encoded
         *  
         *  @since  0.18.5
         */
        Account avatar(const string &avatar);

        /*!
         *  @brief  Returns URL of static avatar
         *  
         *  @since before 0.11.0
         */
        const string avatar_static() const;

        /*!
         *  @brief  Returns true if the account performs automated actions
         *  
         *  @since  0.16.0
         */
        bool bot() const;

        /*!
         *  @brief  Returns time of creation
         *  
         *  @since before 0.11.0
         */
        const system_clock::time_point created_at() const;

        /*!
         *  @brief  Returns display name
         *  
         *  @since before 0.11.0
         */
        const string display_name() const;

        /*!
         *  @brief  Sets display name
         *  
         *  @since  0.18.5
         */
        Account display_name(const string &display_name);

        /*!
         *  @brief  Returns metadata fields
         *  
         *  @since  0.16.1
         */
        const std::vector<fields_pair> fields() const;

        /*!
         *  @brief  Sets metadata fields
         *  
         *  @since  0.18.5
         */
        Account fields(std::vector<fields_pair> &fields);

        /*!
         *  @brief  Returns number of followers
         *  
         *  @since before 0.11.0
         */
        uint_fast64_t followers_count() const;

        /*!
         *  @brief  Returns number of people this account follows
         *  
         *  @since before 0.11.0
         */
        uint_fast64_t following_count() const;

        /*!
         *  @brief  Returns URL of header image
         *  
         *  @since before 0.11.0
         */
        const string header() const;

        /*!
         *  @brief  Sets header image
         *  
         *          Filename or base64-encoded.
         *  
         *  @since  0.18.5
         */
        Account header(const string &header);

        /*!
         *  @brief  Returns URL of static header image
         *  
         *  @since before 0.11.0
         */
        const string header_static() const;

        /*!
         *  @brief  Returns account-ID
         *  
         *  @since before 0.11.0
         */
        const string id() const;

        /*!
         *  @brief  Returns true if the account is locked
         *  
         *  @since before 0.11.0
         */
        bool locked() const;

        /*!
         *  @brief  Sets locked state
         *  
         *  @since  0.18.5
         */
        Account locked(const bool &locked);

        /*!
         *  @brief  Returns true if the account has been moved
         *  
         *  @since before 0.11.0
         */
        bool has_moved() const;

        /*!
         *  @brief  If the owner decided to switch accounts, new account is in
         *          this attribute
         *  
         *  @since before 0.11.0
         */
        const Account moved() const;

        /*!
         *  @brief  Returns note
         *  
         *  @since before 0.11.0
         */
        const string note() const;

        /*!
         *  @brief  Sets note
         *  
         *  @since  0.18.5
         */
        Account note(const string &note);

        /*!
         *  @brief  Returns plaintext version of note
         *  
         *  @since before 0.11.0
         */
        [[deprecated("Will vanish in 1.0.0. Use source() instead.")]]
        const string note_plain() const;

        /*!
         *  @brief  Returns default privacy of new toots
         *  
         *  @since before 0.11.0
         */
        visibility_type privacy() const;

        /*!
         *  @brief  Returns if media is marked as sensitive by default
         *  
         *  @since before 0.11.0
         */
        bool sensitive() const;

        /*!
         *  @brief  Class to hold source attribute
         *  
         *  @since  0.18.5
         */
        class Source : public Easy::Entity
        {
        public:
            /*!
             *  @brief  Constructs an Account::Source object from a JSON string.
             *
             *  @param  json    JSON string
             *  
             *  @since  0.18.5
             */
            explicit Source(const string &json);

            /*!
             *  @brief  Constructs an empty Account::Source object.
             *  
             *  @since  0.18.5
             */
            Source();

            virtual bool valid() const;

            /*!
             *  @brief  Returns metadata fields
             *  
             *  @since  0.18.5
             */
            const std::vector<fields_pair> fields() const;

            /*!
             *  @brief  Sets metadata fields
             *  
             *  @since  0.18.5
             */
            Source fields(std::vector<fields_pair> &fields);

            /*!
             *  @brief  Returns note in plain text
             *  
             *  @since 0.18.5
             */
            const string note() const;

            /*!
             *  @brief  Sets note
             *  
             *  @since  0.18.5
             */
            Source note(const string &note);

            /*!
             *  @brief  Returns default privacy of new toots
             *  
             *  @since 0.18.5
             */
            visibility_type privacy() const;

            /*!
             *  @brief  Sets default privacy of new toots
             *  
             *  @since 0.18.5
             */
            Source privacy(const visibility_type &privacy);

            /*!
             *  @brief  Returns if media is marked as sensitive by default
             *  
             *  @since 0.18.5
             */
            bool sensitive() const;

            /*!
             *  @brief  Sets if media is marked as sensitive by default
             *  
             *  @since 0.18.5
             */
            Source sensitive(const bool &sensitive);
        };

        const Source source() const;
        Account source(const Source &source);

        /*!
         *  @brief  Returns number of statuses
         *  
         *  @since before 0.11.0
         */
        uint_fast64_t statuses_count() const;

        /*!
         *  @brief  Returns URL of the profile
         *  
         *  @since before 0.11.0
         */
        const string url() const;

        /*!
         *  @brief  Returns username (without @hostname)
         *  
         *  @since before 0.11.0
         */
        const string username() const;
};
}

#endif  // MASTODON_CPP_EASY_ACCOUNT_HPP
