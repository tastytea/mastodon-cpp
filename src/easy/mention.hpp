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

#ifndef MASTODON_CPP_EASY_MENTION_HPP
#define MASTODON_CPP_EASY_MENTION_HPP

#include <string>
#include <cstdint>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy.hpp>
#endif

using std::string;
using std::uint64_t;
using std::chrono::system_clock;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold mentions
     */
    class Easy::Mention : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs a Mention object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Mention(const string &json);

        /*!
         *  @brief  Constructs an empty Mention object.
         */
        Mention();

        /*!
         *  @brief  Returns acct
         */
        const string acct() const;

        /*!
         *  @brief  Returns account ID
         */
        const uint64_t id() const;

        /*!
         *  @brief  Returns the URL of user's profile
         */
        const string url() const;

        /*!
         *  @brief  Returns the username of the account
         */
        const string username() const;
    };
}

#endif  // MASTODON_CPP_EASY_MENTION_HPP
