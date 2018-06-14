/*  This file is part of mastodon-cpp.
 *  Copyright © 2018 tastytea <tastytea@tastytea.de>
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

#ifndef MASTODON_CPP_EASY_CONTEXT_HPP
#define MASTODON_CPP_EASY_CONTEXT_HPP

#include <string>
#include <vector>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/easy.hpp"
    #include "easy/entities/status.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/easy.hpp>
    #include <mastodon-cpp/easy/entities/status.hpp>
#endif

using std::string;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold contexts
     *  
     *  @since before 0.11.0
     */
    class Easy::Context : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs a Context object from a JSON string.
         *
         *  @param  json    JSON string
         *  
         *  @since before 0.11.0
         */
        explicit Context(const string &json);

        /*!
         *  @brief  Constructs an empty Context object.
         *  
         *  @since before 0.11.0
         */
        Context();

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

#endif  // MASTODON_CPP_EASY_CONTEXT_HPP
