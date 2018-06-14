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

#ifndef MASTODON_CPP_EASY_INSTANCE_HPP
#define MASTODON_CPP_EASY_INSTANCE_HPP

#include <string>
#include <vector>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/easy.hpp"
    #include "easy/entities/account.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/easy.hpp>
    #include <mastodon-cpp/easy/entities/account.hpp>
#endif

using std::string;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold instances
     *  
     *  @since before 0.11.0
     */
    class Easy::Instance : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs an Instance object from a JSON string.
         *
         *  @param  json    JSON string
         *  
         *  @since before 0.11.0
         */
        explicit Instance(const string &json);

        /*!
         *  @brief  Constructs an empty Instance object.
         *  
         *  @since before 0.11.0
         */
        Instance();

        /*!
         *  @brief  Returns the Account of the admin or another contact person
         *  
         *  @since before 0.11.0
         */
        const Account contact_account() const;

        /*!
         *  @brief  Returns the description of the instance
         *  
         *  @since before 0.11.0
         */
        const string description() const;

        /*!
         *  @brief  Returns the email address which can be used to contact the
         *          instance administrator
         *  
         *  @since before 0.11.0
         */
        const string email() const;

        /*!
         *  @brief  Returns a vector of ISO 6391 language codes the instance has
         *          chosen to advertise
         *  
         *  @since before 0.11.0
         */
        const std::vector<string> languages() const;

        /*!
         *  @brief  Returns the title of the instance
         *  
         *  @since before 0.11.0
         */
        const string title() const;

        /*!
         *  @brief  Returns the URI of the instance
         *  
         *  @since before 0.11.0
         */
        const string uri() const;

        /*!
         *  @brief  Returns the version used by the instance
         *  
         *  @since before 0.11.0
         */
        const string version() const;

        /*!
         *  @brief  Returns the URL for the streaming API
         *  
         *  @since before 0.11.0
         */
        const string streaming_api() const;
    };
}

#endif  // MASTODON_CPP_EASY_INSTANCE_HPP
