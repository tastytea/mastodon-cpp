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

#ifndef MASTODON_CPP_EASY_CONVERSATION_HPP
#define MASTODON_CPP_EASY_CONVERSATION_HPP

#include <string>
#include <vector>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"
#include "account.hpp"
#include "status.hpp"

using std::string;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold conversations.
     *
     *  @since  0.107.0
     */
    class Conversation : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns the id of the conversation.
         *
         *  @since  0.107.0
         */
        const string id() const;

        /*!
         *  @brief  Returns the participating accounts.
         *
         *  @since  0.107.0
         */
        const std::vector<Account> accounts() const;

        /*!
         *  @brief  Returns the last status.
         *
         *  @since  0.107.0
         */
        const Status last_status() const;

        /*!
         *  @brief  Returns true if unread.
         *
         *  @since  0.107.0
         */
        bool unread() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_CONVERSATION_HPP
