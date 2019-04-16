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

#ifndef MASTODON_CPP_EASY_RETURN_TYPES_EASY_HPP
#define MASTODON_CPP_EASY_RETURN_TYPES_EASY_HPP

#include <string>
#include <vector>
#include <ostream>
#include <cstdint>
// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using std::string;
using std::vector;
using std::uint8_t;

namespace Mastodon
{
namespace Easy
{
    template <typename T>
    struct return_entity;
    template <typename T>       // https://stackoverflow.com/a/4661372/5965450
    std::ostream &operator <<(std::ostream&, const return_entity<T>&);

    /*!
     *  @brief  Return types for calls that return a single `Easy::Entity`.
     *
     *  @since  0.100.0
     */
    template <typename T>
    struct return_entity : return_base
    {
        /*!
         *  @brief  Mastodon::Easy::Entity
         *
         *  @since  0.100.0
         */
        T entity;

        return_entity();

        /*!
         *  @brief  Return type for easy Mastodon::Easy::API.
         *
         *  @param ec  Error code
         *  @param em  Error message
         *  @param hec HTTP error code
         *  @param ent Answer
         *
         *  @since  0.100.0
         */
        return_entity(const uint8_t ec, const string &em,
                      const uint16_t hec, const T &ent);

        /*!
         *  @brief  Same as return_entity::entity.
         *
         *  @since  0.100.0
         */
        operator const T() const;

        /*!
         *  @brief  Mastodon::Easy::Entity as string.
         *
         *  @since  0.100.0
         */
        operator const string() const;

        // FIXME: Can't get it to work, don't know why.
        /*!
         *  @brief  Mastodon::Easy::Entity as string.
         *
         *  @since  0.100.0
         */
        friend std::ostream &operator <<<T>(std::ostream &out,
                                            const return_entity<T> &ret);
    };

    /*!
     *  @brief  Return types for calls that return multiple `Easy::Entity`s.
     *
     *  @since  0.100.0
     */
    template <typename T>
    struct return_entity_vector : return_base
    {
        /*!
         *  @brief  std::vector of Mastodon::Easy::Entity.
         *
         *  @since  0.100.0
         */
        vector<T> entities;

        return_entity_vector();
        return_entity_vector(const uint8_t ec, const string &em,
                             const uint16_t hec, const vector<T> &vec);

        /*!
         *  @brief  Same es return_entity_vector::entities.
         *
         *  @since  0.100.0
         */
        operator const vector<T>() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_RETURN_TYPES_EASY_HPP
