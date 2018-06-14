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
#include <functional>
#include <jsoncpp/json/json.h>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using std::string;
using std::uint_fast64_t;
using std::uint_fast16_t;
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

    /*!
     *  @brief Used for stream events.
     */
    typedef std::pair<event_type, string> stream_event;

    /*!
     *  @brief  Map of 'notification type' and 'push is requested or not'
     *
     *          Used in PushSubscription::alerts().
     */
    typedef std::map<Easy::notification_type, bool> alertmap;

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
    class PushSubscription;

    /*!
     *  @brief  Class to hold the `Link`-header.
     *  
     *          Extracts max_id and since_id from the `Link`-header
     */
    class Link
    {
    public:
        /*!
         *  @param  link_header  The content of the `Link` header
         */
        explicit Link(const string &link_header);

        /*!
         *  @brief  Returns max_id
         */
        const uint_fast64_t next() const;

        /*!
         *  @brief  Returns max_id
         */
        const uint_fast64_t max_id() const;

        /*!
         *  @brief  Returns since_id
         */
        const uint_fast64_t prev() const;

        /*!
         *  @brief  Returns since_id
         */
        const uint_fast64_t since_id() const;

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
     *  @brief  Converts a time_point to a string
     *  
     *          The return value can not exceed 1023 chars.
     *
     *  @param  timepoint  The timepoint
     *  @param  format     The format of the string, same as with `strftime`.
     *  
     *  Example:
     *  @code
     *  auto timepoint = status.created_at();
     *  cout << Easy::strtime_utc(timepoint, "%F, %T") << '\n';
     *  @endcode
     *
     *  @return The UTC time as string
     *  
     *  @since  0.11.0
     */
    static const string strtime_utc(const system_clock::time_point &timepoint,
                                    const string &format);

    /*!
     *  @brief  See strtime_utc
     *
     *  @return The local time as string
     *  
     *  @since  0.11.0
     */
    static const string strtime_local(const system_clock::time_point &timepoint,
                                      const string &format);

    // #### simple calls ####
    
    /*!
     *  @brief  Sends a toot.
     *
     *  @param  status  The status to send
     *  @param  error   @ref error "Error code". If the URL has permanently
     *                  changed, 13 is returned and answer is set to the new
     *                  URL.
     *
     *  @return The new Easy::Status
     */
    const Status send_toot(const Status &status, uint_fast16_t error = 0);

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
         */
        const bool was_set() const;

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

        /*!
         *  @brief  Sets the value of key
         *  
         *  @since  0.17.0
         */
        const void set(const string &key, const Json::Value &value);

        const std::uint_fast64_t stouint64(const string &str) const;

    private:
        Json::Value _tree;
        bool _valid;
        mutable bool _was_set;
    };

protected:
    inline static const string strtime
        (const system_clock::time_point &timepoint,
         const string &format, const bool &utc);
};
}

#endif  // MASTODON_EASY_CPP_HPP
