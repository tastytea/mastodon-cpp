/*  This file is part of mastodon-cpp.
 *  Copyright © 2019 tastytea <tastytea@tastytea.de>
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

#ifndef MASTODON_CPP_EASY_POLL_HPP
#define MASTODON_CPP_EASY_POLL_HPP

#include <string>
#include <cstdint>
#include <vector>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"

using std::string;
using std::uint64_t;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold polls.
     *
     *  @since  0.107.0
     */
    class Poll : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns poll ID.
         *
         *  @since  0.107.0
         */
        const string id() const;

        /*!
         *  @brief  Returns time when the poll expires.
         *
         *  @since  0.107.0
         */
        const Easy::time_type expires_at() const;

        /*!
         *  @brief  Returns true if poll has expired.
         *
         *  @since  0.107.0
         */
        bool expired() const;

        /*!
         *  @brief  Returns true or false.
         *
         *  @since  0.107.0
         */
        bool multiple() const;

        /*!
         *  @brief  Returns the number of votes.
         *
         *  @since  0.107.0
         */
        uint64_t votes_count() const;

        /*!
         *  @brief  Returns poll options and their votes count.
         *
         *  @since  0.107.0
         */
        const vector<poll_options_type> options() const;

        /*!
         *  @brief  Returns whether you voted or not.
         *
         *  @since  0.107.0
         */
        bool voted() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_POLL_HPP
