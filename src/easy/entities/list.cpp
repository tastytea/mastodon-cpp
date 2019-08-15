/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
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

#include "list.hpp"

using namespace Mastodon;
using List = Easy::List;
using std::string;
using std::uint64_t;

bool List::valid() const
{
    return Entity::check_valid(
        {
            "id",
            "title"
        });
}

const string List::id() const
{
    return get_string("id");
}

const string List::title() const
{
    return get_string("title");
}
