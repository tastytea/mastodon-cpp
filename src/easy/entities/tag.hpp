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

#ifndef MASTODON_CPP_EASY_TAG_HPP
#define MASTODON_CPP_EASY_TAG_HPP

#include <string>
#include <chrono>
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
using std::chrono::system_clock;
using std::uint_fast64_t;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold tags.
     */
    class Easy::Tag : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Class to hold Tag history
         *  
         *  @since  0.16.0
         */
        class History : public Easy::Entity
        {
        public:
            /*!
             *  @brief  Constructs an Tag::History object from a JSON string.
             *
             *  @param  json    JSON string
             */
            explicit History(const string &json);
            /*!
             *  @brief  Constructs an empty Tag::History object.
             */
            History();

            /*!
             *  @brief  Returns the number of accounts using that hashtag.
             */
            const uint_fast64_t accounts();

            /*!
             *  @brief  Returns the day.
             */
            const system_clock::time_point day();

            /*!
             *  @brief  Returns the number of accounts using that hashtag.
             */
            const uint_fast64_t uses();
        };

        /*!
         *  @brief  Constructs an Tag object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Tag(const string &json);

        /*!
         *  @brief  Constructs an empty Tag object.
         */
        Tag();

        /*!
         *  @brief  Returns the name of the tag
         */
        const string name() const;

        /*!
         *  @brief  Returns the URL of the tag
         */
        const string url() const;

        /*!
         *  @brief  Returns the history of the tag
         *  
         *  @since  0.16.0
         */
        const std::vector<History> history() const;
};
}

#endif  // MASTODON_CPP_EASY_TAG_HPP
