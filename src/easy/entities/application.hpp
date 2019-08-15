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

#ifndef MASTODON_CPP_EASY_APPLICATION_HPP
#define MASTODON_CPP_EASY_APPLICATION_HPP

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
    class Application : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns the name of the application
         *
         *  @since before 0.11.0
         */
        const string name() const;

        /*!
         *  @brief  Returns the website of the application
         *
         *  @since before 0.11.0
         */
        const string website() const;
};
}
}

#endif  // MASTODON_CPP_EASY_APPLICATION_HPP
