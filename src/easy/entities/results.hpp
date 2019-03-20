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

#ifndef MASTODON_CPP_EASY_RESULTS_HPP
#define MASTODON_CPP_EASY_RESULTS_HPP

#include <string>
#include <vector>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/easy.hpp"
    #include "easy/entities/account.hpp"
    #include "easy/entities/status.hpp"
    #include "easy/entities/tag.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/easy.hpp>
    #include <mastodon-cpp/easy/entities/account.hpp>
    #include <mastodon-cpp/easy/entities/status.hpp>
    #include <mastodon-cpp/easy/entities/tag.hpp>
#endif

using std::string;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold results
     *  
     *  @since  before 0.11.0
     */
    class Easy::Results : public Easy::Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const;

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

#endif  // MASTODON_CPP_EASY_RESULTS_HPP
