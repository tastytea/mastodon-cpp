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
#include <vector>
#include <jsoncpp/json/json.h>
#include "instance.hpp"
#include "account.hpp"
#include "macros.hpp"

using namespace Mastodon;
using Instance = Easy::Instance;
using std::string;
using std::uint64_t;

Instance::Instance(const string &json)
: Entity(json)
{}

Instance::Instance()
: Entity()
{}

const Easy::Account Instance::contact_account() const
{
    const Json::Value node = _tree["contact_account"];
    if (node.isObject())
    {
        return Easy::Account(node.toStyledString());
    }

    ttdebug << "Could not get data: contact_account\n";
    return Easy::Account("");
}

const string Instance::description() const
{
    return get_string("description");
}

const string Instance::email() const
{
    return get_string("email");
}

const std::vector<string> Instance::languages() const
{
    return get_vector("languages");
}

const string Instance::title() const
{
    return get_string("title");
}

const string Instance::uri() const
{
    return get_string("uri");
}

const string Instance::version() const
{
    return get_string("version");
}

const std::vector<string> Instance::urls() const
{
    return get_vector("urls");
}
