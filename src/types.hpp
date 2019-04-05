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

#ifndef MASTODON_CPP_TYPES_HPP
#define MASTODON_CPP_TYPES_HPP

#include <string>
#include <map>
#include <vector>

using std::string;

namespace Mastodon
{
    /*!
     *  @brief Used for passing parameters.
     *
     *  Example:
     *  @code
     *  parametermap p =
     *  {
     *      {"field1", { "value1", "value2" } },
     *      {"field2", { "value" } }
     *  }
     *  @endcode
     *
     *  @since  before 0.11.0
     */
    typedef std::map<string, std::vector<string>> parametermap;

    /*!
     *  @brief  HTTP methods.
     *
     *  @since  before 0.100.0
     */
    enum class http_method
    {
        GET,
        PATCH,
        POST,
        PUT,
        DELETE,
        GET_STREAM
    };
}

#endif  // MASTODON_CPP_TYPES_HPP
