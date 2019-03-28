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

#ifndef RETURN_TYPES_EASY_HPP
#define RETURN_TYPES_EASY_HPP

#include <string>
#include <vector>
#include <ostream>
#include <cstdint>
#include "mastodon-cpp.hpp"

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
     */
    template <typename T>
    struct return_entity : return_base
    {
        T entity;

        return_entity();
        return_entity(const uint8_t ec, const string &em, const T &ent);

        operator const T() const;
        operator const string() const;

        // FIXME: Can't get it to work, don't know why.
        friend std::ostream &operator <<<T>(std::ostream &out,
                                            const return_entity<T> &ret);
    };

    /*!
     *  @brief  Return types for calls that return multiple `Easy::Entity`s.
     */
    template <typename T>
    struct return_entity_vector : return_base
    {
        vector<T> entities;

        return_entity_vector();
        return_entity_vector(const uint8_t ec, const string &em,
                             const vector<T> &vec);

        operator const vector<T>() const;
    };
}
}

#endif  // RETURN_TYPES_EASY_HPP
