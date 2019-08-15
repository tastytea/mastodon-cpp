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

#include <algorithm>
#include "types.hpp"

using namespace Mastodon;

param::operator const string() const
{
    return key;
}

const std::vector<param>::const_iterator parameters::find(const string &key)
    const
{
    return std::find_if(this->begin(), this->end(),
                        [&key](const param &p)
                        {
                            if (p.key == key)
                                return true;
                            else
                                return false;
                        });
}
