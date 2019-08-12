/*  This file is part of mastodon-cpp.
 *  Copyright © 2019 tastytea <tastytea@tastytea.de>
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

#ifndef MASTODON_CPP_EASY_TOKEN_HPP
#define MASTODON_CPP_EASY_TOKEN_HPP

#include <string>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"

using std::string;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold applications.
     *
     *  @since before 0.11.0
     */
    class Token : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns the access token.
         *
         *  @since  0.103.0
         */
        const string access_token() const;

        /*!
         *  @brief  Returns the token type.
         *
         *  @since  0.103.0
         */
        const string token_type() const;

        /*!
         *  @brief  Returns the scope of the token.
         *
         *  @since  0.103.0
         */
        const string scope() const;

        /*!
         *  @brief  Returns the date of creation.
         *
         *  @since  0.103.0
         */
        const Easy::time_type created_at() const;
};
}
}

#endif  // MASTODON_CPP_EASY_TOKEN_HPP
