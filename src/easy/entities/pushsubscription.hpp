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

#ifndef MASTODON_CPP_EASY_PUSHSUBSCRIPTION_HPP
#define MASTODON_CPP_EASY_PUSHSUBSCRIPTION_HPP

#include <string>
#include <cstdint>
#include <map>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/easy.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/easy.hpp>
#endif

using std::string;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold push subscriptions.
     *
     *  @since  0.14.0
     */
    class Easy::PushSubscription : public Easy::Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const;

        /*!
         *  @brief  Returns push subscription ID
         *  
         *  @since  0.14.0
         */
        const string id() const;

        /*!
         *  @brief  Returns the endpoint URL
         *  
         *  @since  0.14.0
         */
        const string endpoint() const;

        /*!
         *  @brief  Returns the server public key for signature verification
         *  
         *  @since  0.14.0
         */
        const string server_key() const;

        // TODO: Look up what the data looks like
        /*!
         *  @brief  Returns a map of 'notification event type' and
         *  'push is requested or not'
         *  
         *  @since  0.14.0
         */
        const Easy::alertmap alerts() const;

    protected:
        /*!
         *  @brief  Converts string to bool
         *
         *  @return `true` if str is equal to "true", `false` otherwise
         */
        bool s_to_b(const string &str) const;
};
}

#endif  // MASTODON_CPP_EASY_PUSHSUBSCRIPTION_HPP
