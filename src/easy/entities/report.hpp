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

#ifndef MASTODON_CPP_EASY_REPORT_HPP
#define MASTODON_CPP_EASY_REPORT_HPP

#include <string>
#include <cstdint>

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
     *  @brief  Class to hold reports
     *  
     *  before 0.11.0
     */
    class Easy::Report : public Easy::Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const;

        /*!
         *  @brief  Returns true if an action was taken in response to the
         *          report
         *  
         *  @since  before 0.11.0
         */
        bool action_taken() const;
        
        /*!
         *  @brief  Returns the ID of the report
         *  
         *  @since  before 0.11.0
         */
        const string id() const;
    };
}

#endif  // MASTODON_CPP_EASY_REPORT_HPP
