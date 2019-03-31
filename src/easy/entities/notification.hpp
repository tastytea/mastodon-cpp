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

#ifndef MASTODON_CPP_EASY_NOTIFICATION_HPP
#define MASTODON_CPP_EASY_NOTIFICATION_HPP

#include <string>
#include <cstdint>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/entities/account.hpp"
    #include "easy/entities/status.hpp"
    #include "easy/entity.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/entities/account.hpp>
    #include <mastodon-cpp/easy/entities/status.hpp>
    #include <mastodon-cpp/easy/entity.hpp>
#endif

using std::string;
using std::uint64_t;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold notifications
     *
     *  @since before 0.11.0
     */
    class Notification : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns the Account sending the notification to the user
         *
         *  @since before 0.11.0
         */
        const Account account() const;

        /*!
         *  @brief  Returns time of creation
         *
         *  @since before 0.11.0
         */
        const Easy::time created_at() const;

        /*!
         *  @brief  Returns notification ID
         *
         *  @since before 0.11.0
         */
        const string id() const;

        /*!
         *  @brief  Returns the Status associated with the notification, if
         *          applicable
         *
         *  @since before 0.11.0
         */
        const Status status() const;

        /*!
         *  @brief  Returns notification type
         *
         *  @since before 0.11.0
         */
        Easy::notification_type type() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_NOTIFICATION_HPP
