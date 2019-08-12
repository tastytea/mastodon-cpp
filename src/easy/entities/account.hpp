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

#ifndef MASTODON_CPP_EASY_ACCOUNT_HPP
#define MASTODON_CPP_EASY_ACCOUNT_HPP

#include <string>
#include <cstdint>
#include <vector>
#include <utility>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"
#include "emoji.hpp"

using std::string;
using std::uint64_t;
using std::vector;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold accounts.
     *
     *  @since before 0.11.0
     */
    class Account : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

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
         *  @brief  Returns URL of avatar.
         *
         *  @since before 0.11.0
         */
        const string avatar() const;

        /*!
         *  @brief  Returns URL of static avatar.
         *
         *  @since before 0.11.0
         */
        const string avatar_static() const;

        /*!
         *  @brief  Returns true if the account performs automated actions.
         *
         *  @since  0.16.0
         */
        bool bot() const;

        /*!
         *  @brief  Returns time of creation.
         *
         *  @since before 0.11.0
         */
        const Easy::time_type created_at() const;

        /*!
         *  @brief  Returns display name.
         *
         *  @since before 0.11.0
         */
        const string display_name() const;

        /*!
         *  @brief Returns emojis.
         *
         *  @since 0.106.0
         */
        const std::vector<Easy::Emoji> emojis();

        /*!
         *  @brief  Returns metadata fields.
         *
         *  @since  0.16.1
         */
        const vector<Easy::account_field_type> fields() const;

        /*!
         *  @brief  Returns number of followers.
         *
         *  @since before 0.11.0
         */
        uint64_t followers_count() const;

        /*!
         *  @brief  Returns number of people this account follows.
         *
         *  @since before 0.11.0
         */
        uint64_t following_count() const;

        /*!
         *  @brief  Returns URL of header image.
         *
         *  @since before 0.11.0
         */
        const string header() const;

        /*!
         *  @brief  Returns URL of static header image.
         *
         *  @since before 0.11.0
         */
        const string header_static() const;

        /*!
         *  @brief  Returns account-ID.
         *
         *  @since before 0.11.0
         */
        const string id() const;

        /*!
         *  @brief  Returns true if the account is locked.
         *
         *  @since before 0.11.0
         */
        bool locked() const;

        /*!
         *  @brief  Returns true if the account has been moved. (Deprecated)
         *
         *  @since before 0.11.0
         */
        bool has_moved() const;

        /*!
         *  @brief  If the owner decided to switch accounts, new account is in
         *          this attribute.
         *
         *  @since before 0.11.0
         */
        const Account moved() const;

        /*!
         *  @brief  Returns account description, or biography.
         *
         *  @since before 0.11.0
         */
        const string note() const;

        /*!
         *  @brief  Returns default privacy of new toots.
         *
         *  @since before 0.11.0
         */
        visibility_type privacy() const;

        /*!
         *  @brief  Returns if media is marked as sensitive by default.
         *
         *  @since before 0.11.0
         */
        bool sensitive() const;

        /*!
         *  @brief  Class to hold source attribute.
         *
         *  @since  0.18.5
         */
        class Source : public Entity
        {
        public:
            using Entity::Entity;

            virtual bool valid() const override;

            /*!
             *  @brief  Returns metadata fields.
             *
             *  @since  0.18.5
             */
            const vector<Easy::account_field_type> fields() const;

            /*!
             *  @brief  Returns the language as ISO 6391 string.
             *
             *  @since 0.106.0
             */
            const string language() const;

            /*!
             *  @brief  Returns account description in plain text.
             *
             *  @since 0.18.5
             */
            const string note() const;

            /*!
             *  @brief  Returns default privacy of new toots.
             *
             *  @since 0.18.5
             */
            visibility_type privacy() const;

            /*!
             *  @brief  Returns if media is marked as sensitive by default.
             *
             *  @since 0.18.5
             */
            bool sensitive() const;
        };

        /*!
         *  @brief  Get source.
         *
         *  @since  before 0.100.0
         */
        const Source source() const;

        /*!
         *  @brief  Returns number of statuses
         *
         *  @since before 0.11.0
         */
        uint64_t statuses_count() const;

        /*!
         *  @brief  Returns URL of the profile
         *
         *  @since before 0.11.0
         */
        const string url() const;

        /*!
         *  @brief  Returns username (without \@hostname)
         *
         *  @since before 0.11.0
         */
        const string username() const;
};
}
}

#endif  // MASTODON_CPP_EASY_ACCOUNT_HPP
