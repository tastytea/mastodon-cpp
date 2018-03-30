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

#ifndef MASTODON_CPP_EASY_NOTIFICATION_HPP
#define MASTODON_CPP_EASY_NOTIFICATION_HPP

#include <string>
#include <cstdint>
#include <chrono>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy.hpp"
    #include "account.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy.hpp>
    #include <mastodon-cpp/easy/account.hpp>
#endif

using std::string;
using std::uint64_t;
using std::chrono::system_clock;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold notifications
     */
    class Easy::Notification : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs a Notification object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Notification(const string &json);

        /*!
         *  @brief  Constructs an empty Notification object.
         */
        Notification();

        /*!
         *  @brief  Returns the Account sending the notification to the user
         */
        const Account account() const;

        /*!
         *  @brief  Returns time of creation
         */
        const system_clock::time_point created_at() const;

        /*!
         *  @brief  Returns notification ID
         */
        const uint64_t id() const;

        /*!
         *  @brief  Returns the Status associated with the notification, if
         *          applicable
         */
        // const Status status() const;

        /*!
         *  @brief  Returns notification type
         */
        const Easy::notification_type type() const;
    };
}

#endif  // MASTODON_CPP_EASY_NOTIFICATION_HPP
