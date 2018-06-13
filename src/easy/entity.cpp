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

#include <ctime>
#include <iomanip>  // get_time
#include <sstream>
#include <chrono>
#include <regex>
#include "easy.hpp"
#include "macros.hpp"

using namespace Mastodon;
using std::string;
using std::chrono::system_clock;

Easy::Entity::Entity(const string &json)
: _tree(Json::nullValue)
, _valid(false)
,_was_set(false)
{
    from_string(json);
}

const void Easy::Entity::from_string(const string &json)
{
    std::stringstream ss(json);
    ss >> _tree;

    // If the JSON is a single object encapsulated in an array,
    // transform it into an object. If the JSON string is [], transform to null
    if (_tree.type() == Json::ValueType::arrayValue && _tree.size() <= 1)
    {
        _tree = _tree[0];
    }

    if (_tree.isNull())
    {
        ttdebug << "ERROR: JSON string holds no object\n";
        ttdebug << "String was: " << json << '\n';
    }
    else if (!_tree["error"].isNull())
    {
        ttdebug << "ERROR: Server returned an error\n";
        ttdebug << "String was: " << json << '\n';
    }
    else
    {
        _valid = true;
    }
}

const Json::Value Easy::Entity::to_object() const
{
    return _tree;
}

Easy::Entity::Entity()
: _valid(false)
, _was_set(false)
{}

const bool Easy::Entity::valid() const
{
    return _valid;
}

const string Easy::Entity::error() const
{
    return get_string("error");
}

const bool Easy::Entity::was_set() const
{
    return _was_set;
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
        _was_set = true;
        return *node;
    }

    error:
    ttdebug << "Could not get data: " << key << '\n';
    _was_set = false;
    return Json::Value();
}

const string Easy::Entity::get_string(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isString())
    {
        _was_set = true;
        return node.asString();
    }

    _was_set = false;
    return "";
}

const uint_fast64_t Easy::Entity::get_uint64(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isUInt64())
    {
        _was_set = true;
        return node.asUInt64();
    }

    _was_set = false;
    return 0;
}

const double Easy::Entity::get_double(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isDouble())
    {
        _was_set = true;
        return node.asDouble();
    }

    _was_set = false;
    return 0.0;
}

const bool Easy::Entity::get_bool(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isBool())
    {
        _was_set = true;
        return node.asBool();
    }

    _was_set = false;
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
        _was_set = true;
        return system_clock::from_time_t(time);
    }

    _was_set = false;
    // Return clocks epoch
    return system_clock::time_point();
}

const std::vector<string> Easy::Entity::get_vector(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isArray())
    {
        std::vector<string> vec;
        for (const Json::Value &value : node)
        {
            vec.push_back(value.asString());
        }
        _was_set = true;
        return vec;
    }

    _was_set = false;
    return {};
}

const void Easy::Entity::set(const string &key, const Json::Value &value)
{
    if (key.find('.') == std::string::npos)
    {
        _tree[key] = value;
        return;
    }
    else
    {
        std::size_t pos = 0;
        string current_key = key;
        Json::Value *node = &_tree;

        while ((pos = current_key.find('.')) != std::string::npos)
        {
            try
            {
                node = &(*node)[current_key.substr(0, pos)];
                if (node->isNull())
                {
                    *node = Json::Value(Json::objectValue);
                }
                current_key = current_key.substr(pos + 1);
            }
            catch (const Json::LogicError &e)
            {
                ttdebug << e.what() << '\n';
                goto error;
            }
        }
        (*node)[current_key] = value;
        return;
    }

    error:
    ttdebug << "Could not set data: " << key << '\n';
}

const std::uint_fast64_t Easy::Entity::stouint64(const string &str) const
{
    if (str == "")
    {
        return 0;
    }
    else
    {
        return stoull(str);
    }
}
