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
#include <cstdint>
#include <chrono>
#include <ctime>
#include <iomanip>  // get_time
#include <sstream>
#include <jsoncpp/json/json.h>
#include "easy.hpp"
#include "macros.hpp"

using namespace Mastodon;
using std::string;
using std::uint64_t;
using std::chrono::system_clock;

Easy::Easy(const string &instance, const string &access_token)
: API(instance, access_token)
{}

Easy::Entity::Entity(const string &json)
: _valid(false)
{
    std::stringstream ss(json);
    ss >> _tree;

    if (_tree.isNull())
    {
        ttdebug << "ERROR: JSON string holds no object\n";
        ttdebug << "String was: " << json << '\n';
    }
    else if (_tree["error"].isString())
    {
        ttdebug << "ERROR: Server returned an error\n";
        ttdebug << "String was: " << json << '\n';
    }
    else
    {
        _valid = true;
    }
}

Easy::Entity::Entity()
: _valid(false)
{}

const bool Easy::Entity::valid() const
{
    return _valid;
}

const string Easy::Entity::error() const
{
    return get_string("error");
}

const Json::Value Easy::Entity::get(const string &key) const
{
    const Json::Value *node;
    if (key.find('.') == std::string::npos)
    {
        node = &_tree[key];
    }
    else
    {
        // If dots in key, we have to walk through the tree
        std::size_t pos = 0;
        string current_key = key;
        node = &_tree;
        while ((pos = current_key.find('.')) != std::string::npos)
        {
            try
            {
                node = &(*node)[current_key.substr(0, pos)];
                current_key = current_key.substr(pos + 1);
            }
            catch (const Json::LogicError &e)
            {
                ttdebug << e.what() << '\n';
                goto error;
            }
        }
        node = &(*node)[current_key];
    }

    if (!node->isNull())
    {
        return *node;
    }

    error:
    ttdebug << "Could not get data: " << key << '\n';
    return Json::Value();
}

const string Easy::Entity::get_string(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isString())
    {
        return node.asString();
    }

    return "";
}

const uint64_t Easy::Entity::get_uint64(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isUInt64())
    {
        return node.asUInt64();
    }

    return 0;
}

const double Easy::Entity::get_double(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isDouble())
    {
        return node.asDouble();
    }

    return 0.0;
}

const bool Easy::Entity::get_bool(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isBool())
    {
        return node.asBool();
    }

    return false;
}

const system_clock::time_point
    Easy::Entity::get_time_point(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isString())
    {
        std::stringstream sstime(node.asString());
        struct std::tm tm = {0};
        sstime >> std::get_time(&tm, "%Y-%m-%dT%T");
        std::time_t time = timegm(&tm);
        return system_clock::from_time_t(time);
    }

    // Return clocks epoch
    return system_clock::time_point();
}
