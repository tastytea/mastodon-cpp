/*  This file is part of mastodon-cpp.
 *  Copyright © 2019 tastytea <tastytea@tastytea.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MASTODON_CPP_RETURN_TYPES_HPP
#define MASTODON_CPP_RETURN_TYPES_HPP

#include <cstdint>
#include <string>

using std::uint8_t;
using std::uint16_t;
using std::string;

namespace Mastodon
{
    /*!
     *  @brief  Basis for return types.
     *
     *  @since  0.100.0
     */
    typedef struct return_base
    {
        /*!
         *  @brief  @ref error "Error code".
         *
         *  @since  0.100.0
         */
        uint8_t error_code = 0;

        /*!
         *  @brief  The error message, or "".
         *
         *  @since  0.100.0
         */
        string error_message;

        /*!
         *  @brief HTTP error code.
         *
         *  @since  0.100.0
         */
        uint16_t http_error_code = 0;

        /*!
         *  @brief  true if return_base::error_code is 0, otherwise false.
         *
         *  @since  0.100.0
         */
        operator bool() const;

        /*!
         *  @brief  Same as return_base::error_code.
         *
         *  @since  0.100.0
         */
        operator uint8_t() const;
    } return_base;

    /*!
     *  @brief Return type for API calls.
     *
     *  Example:
     *  @code
     *  Mastodon::return_call ret = masto.get(Mastodon::API::v1::instance);
     *  if (!ret)               // Or ret.error_code != 0
     *  {
     *      cout << "Error " << std::to_string(ret.error_code);
     *      cout << " (HTTP " << std::to_string(ret.http_error_code) << "): ";
     *      cout << ret.error_message << endl
     *  }
     *  else
     *  {
     *      cout << ret << endl; // Or ret.answer
     *  }
     *  @endcode
     *
     *  @since  0.100.0
     */
    typedef struct return_call : return_base
    {
        /*!
         *  @brief  The response from the server.
         *
         *  @since  0.100.0
         */
        string answer;

        return_call();

        /*!
         *  @brief  Return type for Mastodon::API.
         *
         *  @param ec  Error code
         *  @param em  Error message
         *  @param hec HTTP error code
         *  @param a   Answer
         *
         *  @since  0.100.0
         */
        return_call(const uint8_t ec, const string &em,
                    const uint16_t hec, const string &a);

        /*!
         *  @brief  Same es return_call::answer.
         *
         *  @since  0.100.0
         */
        operator const string() const;

        /*!
         *  @brief  Same es return_call::answer.
         *
         *  @since  0.100.0
         */
        friend std::ostream &operator <<(std::ostream &out,
                                         const return_call &ret);
    } return_call;
}

#endif  // MASTODON_CPP_RETURN_TYPES_HPP
