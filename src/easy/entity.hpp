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

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <chrono>
#include <jsoncpp/json/json.h>

using std::string;
using std::chrono::system_clock;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Base class for all entities.
     *
     *  @since  before 0.11.0
     */
    class Entity
    {
    public:
        /*!
         *  @brief  Constructs an Entity object from a JSON string.
         *
         *  @param  json    JSON string
         *
         *  @since  before 0.11.0
         */
        explicit Entity(const string &json);

        /*!
         *  @brief  Constructs an Entity object from a JSON object.
         *
         *  @param  object  JSON object
         *
         *  @since  0.100.0
         */
        explicit Entity(const Json::Value &object);

        /*!
         *  @brief  Constructs an empty Entity object.
         *
         *  @since  before 0.11.0
         */
        Entity();

        /*!
         *  @brief  Destroys the object.
         *
         *  @since  0.100.0
         */
        virtual ~Entity();

        /*!
         *  Returns the JSON object of the Entity
         *
         *  @since  0.100.0
         */
        operator const Json::Value() const;

        /*!
         *  @brief  Replaces the Entity with a new one from a JSON string.
         *
         *  @param  json    JSON string
         *
         *  @since  before 0.11.0
         */
        void from_string(const string &json);

        /*!
         *  @brief  Returns the JSON object of the Entity
         *
         *  @return JSON object
         *
         *  @since  before 0.11.0
         */
        const string to_string() const;

        /*!
         *  @brief  Replaces the Entity with a new one from a JSON object.
         *
         *  @param  object  JSON object
         *
         *  @since  0.100.0
         */
        void from_object(const Json::Value &object);

        /*!
         *  @brief  Returns the JSON object of the Entity
         *
         *  @return JSON object
         *
         *  @since  before 0.11.0
         */
        const Json::Value to_object() const;

        /*!
         *  @brief  Returns true if the Entity holds valid data
         *
         *  @since  before 0.11.0 (virtual since 0.18.2)
         */
        virtual bool valid() const = 0;

        /*!
         *  @brief  Returns error string sent by the server
         *
         *  @since  before 0.11.0
         */
        const string error() const;

        /*!
         *  @brief  Returns true if the last requested value was set, false if
         *          it was unset.
         *
         *          Members of Easy::Entity-derived classes return a default
         *          value depending on its type when the requested value is not
         *          found in the JSON. "" for strings, false for bools and so
         *          on. Most of the time this is no problem, but sometimes you
         *          need to know for sure.
         *
         *  Example:
         *  @code
         *  Easy::Account a(jsonstring);
         *  if (a.note().empty())
         *  {
         *      if (a.was_set())
         *      {
         *          cout << "Account has an empty description.\n";
         *      }
         *      else
         *      {
         *          cout << "Account has no description.\n";
         *      }
         *  }
         *  @endcode
         *
         *  @since  before 0.11.0
         */
        bool was_set() const;

    protected:
        /*!
         *  @brief  Returns the value of key as Json::Value
         *
         *          Returns an empty object if the value does not exist or is
         *          null.
         */
        const Json::Value get(const string &key) const;

        /*!
         *  @brief  Returns the value of key as std::string
         *
         *          returns "" if the value does not exist or is null.
         */
        const string get_string(const string &key) const;

        /*!
         *  @brief  Returns the value of key as std::uint64_t
         *
         *          Returns 0 if the value does not exist or is null.
         */
        uint64_t get_uint64(const string &key) const;

        /*!
         *  @brief  Returns the value of key as double
         *
         *          Returns 0.0 if the value does not exist or is null.
         */
        double get_double(const string &key) const;

        // TODO: Maybe an enum would be better?
        /*!
         *  @brief  Returns the value of key as bool
         *
         *          Returns false if the value does not exist or is null.
         */
        bool get_bool(const string &key) const;

        /*!
         *  @brief  Returns the value of key as time_point
         *
         *          Returns clocks epoch if the value does not exist or is null.
         */
        const system_clock::time_point get_time_point(const string &key) const;

        /*!
         *  @brief  Returns the value of key as vector
         *
         *          Returns an empty vector if the value does not exist or is
         *          null.
         */
        const std::vector<string> get_vector(const string &key) const;

        /*!
         *  @brief  Sets the value of key
         *
         *  @since  0.17.0
         */
        void set(const string &key, const Json::Value &value);

        std::uint64_t stouint64(const string &str) const;

        /*!
         *  @brief  Checks if an Entity is valid
         *
         *  @param  attributes  The attributes to check
         *
         *  @return true if all attributes are set
         *
         *  @since  0.18.2
         */
        bool check_valid(const std::vector<string> &attributes) const;

    private:
        Json::Value _tree;
        mutable bool _was_set;
};
}
}

#endif  // ENTITY_HPP
