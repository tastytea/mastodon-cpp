/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
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
#include <algorithm>
#include "easy/entity.hpp"
#include "debug.hpp"

using namespace Mastodon;
using std::string;
using std::chrono::system_clock;

Easy::Entity::Entity(const string &json)
: _tree(Json::nullValue)
,_was_set(false)
{
    from_string(json);
}

Easy::Entity::Entity(const Json::Value &object)
: _tree(object)
,_was_set(false)
{}

Easy::Entity::Entity()
: _tree(Json::nullValue)
, _was_set(false)
{}

Easy::Entity::~Entity()
{}

Easy::Entity::operator const Json::Value() const
{
    return to_object();
}

void Easy::Entity::from_string(const string &json)
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
}

const string Easy::Entity::to_string() const
{
    return _tree.toStyledString();
}

void Easy::Entity::from_object(const Json::Value &object)
{
    _tree = object;
}

const Json::Value Easy::Entity::to_object() const
{
    return _tree;
}

bool Easy::Entity::check_valid(const std::vector<string> &attributes) const
{
    for (const string &attribute: attributes)
    {
        get(attribute);
        if (!was_set())
        {
            return false;
        }
    }

    return true;
}

const string Easy::Entity::error() const
{
    return get_string("error");
}

bool Easy::Entity::was_set() const
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

uint64_t Easy::Entity::get_uint64(const string &key) const
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

double Easy::Entity::get_double(const string &key) const
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

bool Easy::Entity::get_bool(const string &key) const
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

const Easy::time Easy::Entity::get_time(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isString())
    {
        std::stringstream sstime(node.asString());
        struct std::tm tm;
        sstime >> std::get_time(&tm, "%Y-%m-%dT%T");
        std::time_t time = timegm(&tm);
        _was_set = true;
        return { system_clock::from_time_t(time) };
    }

    _was_set = false;
    // Return clocks epoch
    return { system_clock::time_point() };
}

const std::vector<string> Easy::Entity::get_vector(const string &key) const
{
    const Json::Value node = get(key);

    if (node.isArray())
    {
        std::vector<string> vec;
        std::transform(node.begin(), node.end(), std::back_inserter(vec),
                       [](const Json::Value &value)
                           { return value.asString(); });
        _was_set = true;
        return vec;
    }

    _was_set = false;
    return {};
}

void Easy::Entity::set(const string &key, const Json::Value &value)
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

std::uint64_t Easy::Entity::stouint64(const string &str) const
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

// Easy::GenericEntity::GenericEntity(const string &json)
// : Entity(json)
// {}

// Easy::GenericEntity::GenericEntity()
// : Entity()
// {}

// bool Easy::GenericEntity::valid() const
// {
//     return true;
// }

// template<typename T> GenericEntity<T>::GenericEntity(const string &json)
//     : Entity(json)
// {}

// template<typename T> GenericEntity<T>::GenericEntity()
//     : Entity()
// {}

// template<typename T> bool GenericEntity<T>::valid() const
// {
//     return true;
// }
