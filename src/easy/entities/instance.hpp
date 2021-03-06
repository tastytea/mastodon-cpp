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

#ifndef MASTODON_CPP_EASY_INSTANCE_HPP
#define MASTODON_CPP_EASY_INSTANCE_HPP

#include <string>
#include <vector>

using std::uint64_t;

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"
#include "account.hpp"

using std::string;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold instances.
     *
     *  @since  before 0.11.0
     */
    class Instance : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns the Account of the admin or another contact person.
         *
         *  @since  before 0.11.0
         */
        const Account contact_account() const;

        /*!
         *  @brief  Returns the description of the instance.
         *
         *  @since  before 0.11.0
         */
        const string description() const;

        /*!
         *  @brief  Returns the email address which can be used to contact the
         *          instance administrator.
         *
         *  @since  before 0.11.0
         */
        const string email() const;

        /*!
         *  @brief  Returns a vector of ISO 6391 language codes the instance has
         *          chosen to advertise.
         *
         *  @since  before 0.11.0
         */
        const vector<string> languages() const;

        /*!
         *  @brief  Returns the thumbnail of the instance.
         *
         *  @since  0.106.0
         */
        const string thumbnail() const;

        /*!
         *  @brief  Returns the title of the instance.
         *
         *  @since  before 0.11.0
         */
        const string title() const;

        /*!
         *  @brief  Returns the URI of the instance.
         *
         *  @since  before 0.11.0
         */
        const string uri() const;

        /*!
         *  @brief  Returns the URL for the streaming API and possibly others.
         *
         *  @since  0.106.0
         */
        const Easy::urls_type urls() const;

        /*!
         *  @brief  Returns statistics about the instance.
         *
         *  @since  0.106.0
         */
        const Easy::stats_type stats() const;

        /*!
         *  @brief  Returns the version used by the instance.
         *
         *  @since  before 0.11.0
         */
        const string version() const;

        /*!
         *  @brief  Returns the maximum chars a post can have
         *
         *          This parameter is not supported by upstream Mastodon. If it
         *          is not found, 500 is returned.
         *
         *  @since  0.20.0
         */
        uint64_t max_toot_chars() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_INSTANCE_HPP
