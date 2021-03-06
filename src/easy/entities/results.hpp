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

#ifndef MASTODON_CPP_EASY_RESULTS_HPP
#define MASTODON_CPP_EASY_RESULTS_HPP

#include <string>
#include <vector>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"
#include "account.hpp"
#include "status.hpp"
#include "tag.hpp"

using std::string;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold results
     *
     *  @since  before 0.11.0
     */
    class Results : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns an array of matched Accounts
         *
         *  @since  before 0.11.0
         */
        const std::vector<Account> accounts() const;

        /*!
         *  @brief  Returns an array of matched Statuses
         *
         *  @since  before 0.11.0
         */
        const std::vector<Status> statuses() const;

        /*!
         *  @brief  Returns an array of matched hashtags as string
         *
         *  @since  0.16.0
         */
        const std::vector<string> hashtags_v1() const;

        /*!
         *  @brief  Returns an array of matched hashtags as Easy::Tag
         *
         *  @since  0.16.0
         */
        const std::vector<Tag> hashtags_v2() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_RESULTS_HPP
