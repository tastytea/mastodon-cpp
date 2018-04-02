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
#include <utility>
#include <jsoncpp/json/json.h>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using std::string;
using std::uint_fast64_t;
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
     *  @brief  Describes the event type
     */
    enum class event_type
    {
        Update,
        Notification,
        Delete,
        Undefined
    };

    /*!
     *  @brief  Describes visibility of toots.
     */
    enum class visibility_type
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
        Image,
        Video,
        Gifv,
        Unknown,
        Undefined
    };

    /*!
     *  @brief  Describes the card type
     */
    enum class card_type
    {
        Link,
        Photo,
        Video,
        Rich,
        Undefined
    };

    /*!
     *  @brief  Describes the notification type
     */
    enum class notification_type
    {
        Mention,
        Reblog,
        Favourite,
        Follow,
        Undefined
    };

    typedef std::pair<event_type, string> stream_event;

    /*!
     *  @brief  Class to hold the `Link`-header.
     *  
     *          Extracts max_id and since_id from the `Link:`-header
     */
    class Link
    {
    public:
        explicit Link(const string &link_header);

        /*!
         *  @brief  Returns max_id
         */
        const uint_fast64_t next() const;

        /*!
         *  @brief  Returns since_id
         */
        const uint_fast64_t prev() const;

    private:
        uint_fast64_t _next;
        uint_fast64_t _prev;
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
     *  @brief  Turns a JSON array into a vector of strings
     *
     *  @param  json    JSON string holding the array
     *
     *  @return vector of strings or an empty vector on error
     */
    static const std::vector<string> json_array_to_vector(const string &json);

    /*!
     *  @brief  Split stream into a vector of events
     *
     *  @param  streamdata  Data from get_stream()
     *
     *  @return vector of stream events
     */
    static const std::vector<stream_event>
        parse_stream(const std::string &streamdata);

    /*!
     *  @brief  Gets the links from the last answer
     */
    const Link get_link() const;

    /*!
     *  @brief  Base class for all entities.
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
         *  @brief  Replaces the Entity with a new one from a JSON string.
         *
         *  @param  json    JSON string
         */
        const void from_string(const string &json);

        /*!
         *  @brief  Returns the JSON object of the Entity
         *
         *  @return JSON object
         */
        const Json::Value to_object() const;

        /*!
         *  @brief  Returns true if the Entity holds valid data
         */
        const bool valid() const;

        /*!
         *  @brief  Returns error string sent by the server
         */
        const string error() const;

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
         *  @brief  Returns the value of key as std::uint_fast64_t
         *  
         *          Returns 0 if the value does not exist or is null.
         */
        const uint_fast64_t get_uint64(const string &key) const;

        /*!
         *  @brief  Returns the value of key as double
         *  
         *          Returns 0.0 if the value does not exist or is null.
         */
        const double get_double(const string &key) const;

        // TODO: Maybe an enum would be better?
        /*!
         *  @brief  Returns the value of key as bool
         *  
         *          Returns false if the value does not exist or is null.
         */
        const bool get_bool(const string &key) const;

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

        Json::Value _tree;
        bool _valid;
    };

    class Account;
    class Application;
    class Attachment;
    class Card;
    class Context;
    class Emoji;
    class Instance;
    class List;
    class Mention;
    class Notification;
    class Relationship;
    class Report;
    class Results;
    class Status;
    class Tag;
};
}

#endif  // MASTODON_EASY_CPP_HPP
