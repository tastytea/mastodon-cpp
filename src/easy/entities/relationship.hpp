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

#ifndef MASTODON_CPP_EASY_RELATIONSHIP_HPP
#define MASTODON_CPP_EASY_RELATIONSHIP_HPP

#include <string>
#include <cstdint>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/easy.hpp"
    #include "easy/entity.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/easy.hpp>
    #include <mastodon-cpp/easy/entity.hpp>
#endif

using std::string;
using std::uint64_t;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold relationships
     *
     *  before 0.11.0
     */
    class Relationship : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const;

        /*!
         *  @brief  Returns true if the user is blocking the account
         *
         *  @since  before 0.11.0
         */
        bool blocking() const;

        /*!
         *  @brief  Returns true if the user is blocking the account's domain
         *
         *  @since  before 0.11.0
         */
        bool domain_blocking() const;

        /*!
         *  @brief  Returns true if the account is endorsed by the user
         *
         *  @since  0.19.0
         */
        bool endorsed() const;

        /*!
         *  @brief  Returns true if the user is being followed by the account
         *
         *  @since  before 0.11.0
         */
        bool followed_by() const;

        /*!
         *  @brief  Returns true if the user is being following the account
         *
         *  @since  before 0.11.0
         */
        bool following() const;

        /*!
         *  @brief  Returns the target account ID
         *
         *  @since  before 0.11.0
         */
        const string id() const;

        /*!
         *  @brief  Returns true if the user is muting the account
         *
         *  @since  before 0.11.0
         */
        bool muting() const;

        /*!
         *  @brief  Returns true if the user is also muting notifications
         *
         *  @since  before 0.11.0
         */
        bool muting_notifications() const;

        /*!
         *  @brief  Returns true if the user has requested to follow the account
         *
         *  @since  before 0.11.0
         */
        bool requested() const;

        /*!
         *  @brief  Returns true if the user is showing notifications
         *
         *  @since  0.19.0
         */
        bool showing_notifications() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_RELATIONSHIP_HPP
