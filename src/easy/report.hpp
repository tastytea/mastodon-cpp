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

#ifndef MASTODON_CPP_EASY_REPORT_HPP
#define MASTODON_CPP_EASY_REPORT_HPP

#include <string>
#include <cstdint>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy.hpp>
#endif

using std::string;
using std::uint64_t;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold reports
     */
    class Easy::Report : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs a Report object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Report(const string &json);

        /*!
         *  @brief  Constructs an empty Report object.
         */
        Report();

        /*!
         *  @brief  Returns true if an action was taken in response to the
         *          report
         */
        const bool action_taken() const;
        
        /*!
         *  @brief  Returns the ID of the report
         */
        const uint64_t id() const;
    };
}

#endif  // MASTODON_CPP_EASY_REPORT_HPP
