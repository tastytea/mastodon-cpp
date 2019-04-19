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

#ifndef MASTODON_CPP_EASY_FILTER_HPP
#define MASTODON_CPP_EASY_FILTER_HPP

#include <string>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/entity.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/entity.hpp>
#endif

using std::string;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold filters.
     *
     *  @since  0.104.0
     */
    class Filter : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns the id of the filter
         *
         *  @since  0.104.0
         */
        const string id() const;

        /*!
         *  @brief  Returns the phrase to filter.
         *
         *  @since  0.104.0
         */
        const string phrase() const;

        /*!
         *  @brief  Returns the contexts in which to filter.
         *
         *  @since  0.104.0
         */
        const vector<Easy::context_type> context() const;

        /*!
         *  @brief  Returns the expiration time of the filter.
         *
         *  @since  0.104.0
         */
        const Easy::time expires_at() const;

        /*!
         *  @brief  Returns if the phrase should disappear irreversibly.
         *
         *  If set to true, the filtered posts will be hidden even if filter is
         *  later removed.
         *
         *  @since  0.104.0
         */
        bool irreversible() const;

        /*!
         *  @brief Returns if the filter should only be applied if it matches
         *  the whole word.
         *
         *  @since  0.104.0
         */
        bool whole_word() const;
};
}
}

#endif  // MASTODON_CPP_EASY_FILTER_HPP
