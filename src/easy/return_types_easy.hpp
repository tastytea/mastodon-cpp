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
#include "mastodon-cpp.hpp"

using std::string;
using std::vector;

namespace Mastodon
{
template <typename T>
struct return_entity;
// https://stackoverflow.com/a/4661372/5965450
template <typename T>
std::ostream &operator <<(std::ostream&, const return_entity<T>&);

template <typename T>
struct return_entity : return_base
{
    T entity;

    return_entity();
    return_entity(const uint8_t ec, const string &em, const T &ent);

    operator const T() const;
    operator const string() const;

    friend std::ostream &operator <<<T>(std::ostream &out,
                                     const return_entity<T> &ret);
};

template <typename T>
struct return_entity_vector : return_base
{
    vector<T> entities;

    return_entity_vector();
    return_entity_vector(const uint8_t ec, const string &em,
                         const vector<T> &vec);

    operator const vector<T>() const;
};


template<typename T>
return_entity<T>::return_entity()
    : entity()
{}

template<typename T>
return_entity<T>::return_entity(const uint8_t ec, const string &em,
                                const T &ent)
    : entity(ent)
{
    error_code = ec;
    error_message = em;
}

template<typename T>
return_entity<T>::return_entity::operator const T() const
{
    return entity;
}

template<typename T>
return_entity<T>::return_entity::operator const string() const
{
    return entity.to_string();
}

template<typename T>
std::ostream &operator <<(std::ostream &out, const return_entity<T> &ret)
{
    out << ret.entity.to_string();
    return out;
}

// Explicit instantiation
// template struct Mastodon::return_entity<Easy::Status>;

template<typename T>
return_entity_vector<T>::return_entity_vector::return_entity_vector()
: entities()
{}

template<typename T>
return_entity_vector<T>::return_entity_vector::return_entity_vector(
    const uint8_t ec, const string &em, const vector<T> &vec)
: entities(vec)
{
    error_code = ec;
    error_message = em;
}

template<typename T>
return_entity_vector<T>::return_entity_vector::operator const vector<T>() const
{
    return entities;
}
}

#endif  // RETURN_TYPES_EASY_HPP
