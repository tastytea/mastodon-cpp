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

#ifndef MASTODON_EASY_CPP_HPP
#define MASTODON_EASY_CPP_HPP

#include <string>
#include <cstdint>
#include <chrono>
#include <vector>
#include <jsoncpp/json/json.h>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using std::string;
using std::uint64_t;
using std::chrono::system_clock;

namespace Mastodon
{
/*!
 *  @brief  Child of Mastodon::API with abstract methods.
 */
class Easy : public API
{
public:
    /*!
     *  @brief  Describes visibility of toots.
     *  
     *          The names begin with a capital letter because some of them
     *          are reserved keywords when written in all-lowercase.
     */
    enum class visibility
    {
        Direct,
        Private,
        Unlisted,
        Public,
        Undefined
    };

    /*!
     *  @brief  Describes the attachment type
     */
    enum class attachment_type
    {
        image,
        video,
        gifv,
        unknown
    };

    /*!
     *  @brief  Describes the card type
     */
    enum class card_type
    {
        link,
        photo,
        video,
        rich,
        unknown
    };

    /*!
     *  @brief  Constructs a new Easy object.
     *  
     *          To register your application, leave access_token blank and call
     *          register_app1() and register_app2().
     *
     *  @param  instance      The hostname of your instance
     *  @param  access_token  The access token
     */
    explicit Easy(const string &instance, const string &access_token);

    /*!
     *  @brief  Base class for entities.
     */
    class Entity
    {
    public:
        /*!
         *  @brief  Constructs an Entity object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Entity(const string &json);

        /*!
         *  @brief  Constructs an empty Entity object.
         */
        Entity();

        /*!
         *  @brief  Returns true if the Entity holds valid data
         */
        const bool valid() const;

        /*!
         *  @brief  Returns error string
         */
        const string error() const;

        /*!
         *  @brief  Returns the value of node as Json::Value
         *  
         *          Returns an empty object on error.
         */
        const Json::Value get(const string &key) const;

        /*!
         *  @brief  Returns the value of node as std::string
         *  
         *          returns "" on error.
         */
        const string get_string(const string &key) const;

        /*!
         *  @brief  Returns the value of node as std::uint64_t
         *  
         *          Returns 0 on error.
         */
        const uint64_t get_uint64(const string &key) const;

        /*!
         *  @brief  Returns the value of node as double
         *  
         *          Returns 0.0 on error.
         */
        const double get_double(const string &key) const;

        // TODO: Investigate if uint8_t would be better
        /*!
         *  @brief  Returns the value of node as bool
         *  
         *          Returns false on error.
         */
        const bool get_bool(const string &key) const;

        /*!
         *  @brief  Returns the value of node as time_point
         *  
         *          Returns clocks epoch on error.
         */
        const system_clock::time_point get_time_point(const string &key) const;

        /*!
         *  @brief  Returns the value of node as vector
         *  
         *          Returns false on error.
         */
        const std::vector<string> get_vector(const string &key) const;

    protected:
        Json::Value _tree;
        bool _valid;
    };

    class Account;
    class Attachment;
    class Card;
    class Context;
    class Emoji;
    class Instance;
};
}

#endif  // MASTODON_EASY_CPP_HPP
