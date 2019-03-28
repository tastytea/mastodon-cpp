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

#ifndef MASTODON_CPP_EASY_TAG_HPP
#define MASTODON_CPP_EASY_TAG_HPP

#include <string>
#include <chrono>
#include <cstdint>
#include "easy/entity.hpp"

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
using std::uint64_t;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold tags.
     *  
     *  @since  before 0.11.0
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
            using Entity::Entity;

            virtual bool valid() const;

            /*!
             *  @brief  Returns the number of accounts using that hashtag.
             *  
             *  @since  0.16.0
             */
            uint64_t accounts();

            /*!
             *  @brief  Returns the day.
             *  
             *  @since  0.16.0
             */
            const system_clock::time_point day();

            /*!
             *  @brief  Returns the number of accounts using that hashtag.
             *  
             *  @since  0.16.0
             */
            uint64_t uses();
        };

        using Entity::Entity;

        virtual bool valid() const;

        /*!
         *  @brief  Returns the name of the tag
         *  
         *  @since  before 0.11.0
         */
        const string name() const;

        /*!
         *  @brief  Returns the URL of the tag
         *  
         *  @since  before 0.11.0
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
