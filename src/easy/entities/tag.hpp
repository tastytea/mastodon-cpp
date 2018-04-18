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

#ifndef MASTODON_CPP_EASY_TAG_HPP
#define MASTODON_CPP_EASY_TAG_HPP

#include <string>

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
     *  @brief  Class to hold tags.
     */
    class Easy::Tag : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs an Tag object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Tag(const string &json);

        /*!
         *  @brief  Constructs an empty Tag object.
         */
        Tag();

        /*!
         *  @brief  Returns the name of the application
         */
        const string name() const;

        /*!
         *  @brief  Returns the URL of the application
         */
        const string url() const;
};
}

#endif  // MASTODON_CPP_EASY_TAG_HPP