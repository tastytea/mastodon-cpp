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

#include "return_types_easy.hpp"
#include "easy/entities/status.hpp"
#include "easy/entities/notification.hpp"

using namespace Mastodon;

template<typename T>
Easy::return_entity<T>::return_entity()
    : entity()
{}

template<typename T>
Easy::return_entity<T>::return_entity(const uint8_t ec, const string &em,
                                      const T &ent)
    : entity(ent)
{
    error_code = ec;
    error_message = em;
}

template<typename T>
Easy::return_entity<T>::return_entity::operator const T() const
{
    return entity;
}

template<typename T>
Easy::return_entity<T>::return_entity::operator const string() const
{
    return entity.to_string();
}

template<typename T>
std::ostream &Easy::operator <<(std::ostream &out,
                                const Easy::return_entity<T> &ret)
{
    out << ret.entity.to_string();
    return out;
}

// Explicit instantiations, so it can be used from outside.
// TODO: Complete this.
template struct Easy::return_entity<Easy::Status>;
template struct Easy::return_entity<Easy::Notification>;


template<typename T>
Easy::return_entity_vector<T>::
return_entity_vector::return_entity_vector()
    : entities()
{}

template<typename T>
Easy::return_entity_vector<T>::return_entity_vector::return_entity_vector(
    const uint8_t ec, const string &em, const vector<T> &vec)
    : entities(vec)
{
    error_code = ec;
    error_message = em;
}

template<typename T>
Easy::return_entity_vector<T>::return_entity_vector::operator const vector<T>()
    const
{
    return entities;
}

// Explicit instantiations, so it can be used from outside.
// TODO: Complete this.
template struct Easy::return_entity_vector<Easy::Status>;
template struct Easy::return_entity_vector<Easy::Notification>;
