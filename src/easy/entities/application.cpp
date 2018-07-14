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

#include "application.hpp"

using namespace Mastodon;
using Application = Easy::Application;

Application::Application(const string &json)
: Entity(json)
{}

Application::Application()
: Entity()
{}

const bool Application::valid() const
{
    return Entity::check_valid({"name"});
}

const string Application::name() const
{
    return get_string("name");
}

const string Application::website() const
{
    return get_string("website");
}
