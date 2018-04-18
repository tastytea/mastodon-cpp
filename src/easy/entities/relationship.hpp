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

#ifndef MASTODON_CPP_EASY_RELATIONSHIP_HPP
#define MASTODON_CPP_EASY_RELATIONSHIP_HPP

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

namespace Mastodon
{
    /*!
     *  @brief  Class to hold relationships
     */
    class Easy::Relationship : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs a Relationship object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Relationship(const string &json);

        /*!
         *  @brief  Constructs an empty Relationship object.
         */
        Relationship();

        /*!
         *  @brief  Returns true if the user is blocking the account
         */
        const bool blocking() const;

        /*!
         *  @brief  Returns true if the user is blocking the account's domain
         */
        const bool domain_blocking() const;

        /*!
         *  @brief  Returns true if the user is being followed by the account
         */
        const bool followed_by() const;

        /*!
         *  @brief  Returns true if the user is being following the account
         */
        const bool following() const;

        /*!
         *  @brief  Returns the target account ID
         */
        const uint_fast64_t id() const;

        /*!
         *  @brief  Returns true if the user is muting the account
         */
        const bool muting() const;

        /*!
         *  @brief  Returns true if the user is also muting notifications
         */
        const bool muting_notifications() const;

        /*!
         *  @brief  Returns true if the user has requested to follow the account
         */
        const bool requested() const;
    };
}

#endif  // MASTODON_CPP_EASY_RELATIONSHIP_HPP