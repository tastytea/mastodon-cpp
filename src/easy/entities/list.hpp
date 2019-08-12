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

#ifndef MASTODON_CPP_EASY_LIST_HPP
#define MASTODON_CPP_EASY_LIST_HPP

#include <string>
#include <vector>
#include <cstdint>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"

using std::string;
using std::uint64_t;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold lists
     *
     *  @since before 0.11.0
     */
    class List : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns list-ID
         *
         *  @since before 0.11.0
         */
        const string id() const;

        /*!
         *  @brief  Returns title
         *
         *  @since before 0.11.0
         */
        const string title() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_LIST_HPP
