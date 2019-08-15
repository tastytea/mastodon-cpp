/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MASTODON_CPP_EASY_CONTEXT_HPP
#define MASTODON_CPP_EASY_CONTEXT_HPP

#include <string>
#include <vector>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"
#include "status.hpp"

using std::string;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold contexts
     *
     *  @since before 0.11.0
     */
    class Context : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns the ancestors of the Status as vector of Statuses
         *
         *  @since before 0.11.0
         */
        const std::vector<Status> ancestors() const;

        /*!
         *  @brief  Returns the descendants of the Status as vector of Statuses
         *
         *  @since before 0.11.0
         */
        const std::vector<Status> descendants() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_CONTEXT_HPP
