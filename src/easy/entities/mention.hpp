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
     *  @brief  Class to hold mentions
     *  
     *  before 0.11.0
     */
    class Easy::Mention : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs a Mention object from a JSON string.
         *
         *  @param  json    JSON string
         *  
         *  @since before 0.11.0
         */
        explicit Mention(const string &json);

        /*!
         *  @brief  Constructs an empty Mention object.
         *  
         *  @since before 0.11.0
         */
        Mention();

        /*!
         *  @brief  Returns acct
         *  
         *  @since before 0.11.0
         */
        const string acct() const;

        /*!
         *  @brief  Returns account ID
         *  
         *  @since before 0.11.0
         */
        const uint_fast64_t id() const;

        /*!
         *  @brief  Returns the URL of user's profile
         *  
         *  @since before 0.11.0
         */
        const string url() const;

        /*!
         *  @brief  Returns the username of the account
         *  
         *  @since before 0.11.0
         */
        const string username() const;
    };
}

#endif  // MASTODON_CPP_EASY_MENTION_HPP
