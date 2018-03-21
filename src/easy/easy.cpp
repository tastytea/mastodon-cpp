/*  This file is part of mastodon-cpp.
 *  Copyright © 2018 tastytea <tastytea@tastytea.de>
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

#include <string>
#include <sstream>
#include "easy.hpp"
#include "macros.hpp"

using namespace Mastodon;
using std::string;

Easy::Easy(const string &instance, const string &access_token)
: API(instance, access_token)
{
    //
}

Easy::Entity::Entity(const string &json)
: _valid(false)
{
    std::stringstream ss(json);
    ss >> _tree;

    if (_tree.isNull())
    {
        std::cerr << "ERROR: Could not build Entity from JSON string\n";
        ttdebug << "String was: " << json << '\n';
    }
    else
    {
        _valid = true;
    }
}

const bool Easy::Entity::valid() const
{
    return _valid;
}
