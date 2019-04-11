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
using std::vector;

namespace Mastodon
{
    /*!
     *  @brief  A single parameter.
     *
     *  @param  key    The key as a string.
     *  @param  values The values as a vector of strings.
     *
     *  @since  0.100.0
     */
    typedef struct param
    {
        string key;
        vector<string> values;

        /*!  @brief  Returns key  */
        operator const string() const;
    } param;

    /*!
     *  @brief  Vector of Mastodon::param, used for passing parameters in calls.
     *
     *  The only difference to a std::vector<param> is the added member find.
     *
     *  Example:
     *  @code
     *  parameters p =
     *      {
     *          { "media_ids", { "1234", "4321" } },
     *          { "status", { "Hello world!" } }
     *      };
     *  @endcode
     *
     *  @since  0.100.0
     */
    typedef struct parameters : public vector<param>
    {
        using vector<param>::vector;

        /*!
         *  @brief  Get iterator to element with key.
         *
         *  Searches parameters for an element with a key equivalent to key and
         *  returns an iterator to it if found, otherwise it returns an iterator
         *  to parameters::end().
         *
         *  @param  key String to search for.
         *
         *  @return Iterator to element with key or parameters::end().
         *
         *  @since  0.100.0
         */
        const std::vector<param>::const_iterator find(const string &key) const;
    } parameters;

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
