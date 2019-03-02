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
using std::vector;
using std::uint64_t;
using std::uint16_t;
using std::chrono::system_clock;

namespace Mastodon
{
// Defined at the bottom
typedef struct return_entity return_entity;
typedef struct return_entity_vector return_entity_vector;

/*!
 *  @brief  Child of Mastodon::API with abstract methods.
 *  
 *  @since  before 0.11.0
 */
class Easy : public API
{
public:
    /*!
     *  @brief  Describes the event type
     *  
     *  @since  before 0.11.0
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
     *  
     *  @since  before 0.11.0
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
     *  
     *  @since  before 0.11.0
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
     *  
     *  @since  before 0.11.0
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
     *  
     *  @since  before 0.11.0
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
     *  
     *  @since  before 0.11.0
     */
    typedef std::pair<event_type, string> stream_event;

    /*!
     *  @brief  Map of 'notification type' and 'push is requested or not'
     *
     *          Used in PushSubscription::alerts().
     *  
     *  @since  0.13.3
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
     *  
     *  @since  before 0.11.0
     */
    class Link
    {
    public:
        /*!
         *  @param  link_header  The content of the `Link` header
         *  
         *  @since  before 0.11.0
         */
        explicit Link(const string &link_header);

        /*!
         *  @brief  Returns max_id
         *  
         *  @since  before 0.11.0
         */
        const string next() const;

        /*!
         *  @brief  Returns max_id
         *  
         *  @since  before 0.11.0
         */
        const string max_id() const;

        /*!
         *  @brief  Returns since_id
         *  
         *  @since  before 0.11.0
         */
        const string prev() const;

        /*!
         *  @brief  Returns since_id
         *  
         *  @since  before 0.11.0
         */
        const string since_id() const;

    private:
        string _next;
        string _prev;
    };

    /*!
     *  @brief  Constructs a new Easy object.
     *  
     *          To register your application, leave access_token blank and call
     *          register_app1() and register_app2().
     *
     *  @param  instance      The hostname of your instance
     *  @param  access_token  The access token
     *  
     *  @since  before 0.11.0
     */
    explicit Easy(const string &instance, const string &access_token);

    /*!
     *  @brief  Turns a JSON array into a vector of strings
     *
     *  @param  json    JSON string holding the array
     *
     *  @return vector of strings or an empty vector on error
     *  
     *  @since  before 0.11.0
     */
    static const std::vector<string> json_array_to_vector(const string &json);

    /*!
     *  @brief  Split stream into a vector of events
     *
     *  @param  streamdata  Data from get_stream()
     *
     *  @return vector of stream events
     *  
     *  @since  before 0.11.0
     */
    static const std::vector<stream_event>
        parse_stream(const std::string &streamdata);

    /*!
     *  @brief  Gets the links from the last answer
     *  
     *  @since  before 0.11.0
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
     *  @param  error   @ref error "Error code"
     *
     *  @return The new Easy::Status
     *  
     *  @since  0.18.1
     */
    const return_entity send_post(const Status &status);

    /*!
     *  @brief  Alias for send_post()
     *  
     *  @since  0.17.0
     */
    const return_entity send_toot(const Status &status);

    /*!
     *  @brief  Gets notifications.
     *
     *  @param  error     @ref error "Error code"
     *  @param  limit     Maximum number of notifications
     *  @param  since_id  Return notifications newer than ID
     *  @param  max_id    Return notifications older than ID
     *
     *  @return vector of Easy::Notification.
     *
     *  @since  0.21.0
     */
    const return_entity_vector get_notifications(const uint16_t limit = 20,
                                                 const string since_id = 0,
                                                 const string max_id = 0);

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

    /*!
     *  @brief  Class to hold generic entities.
     *
     *  @since  0.100.0
     */
    class GenericEntity : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs an GenericEntity object from a JSON string.
         *
         *  @param  json    JSON string
         *
         *  @since  0.100.0
         */
        explicit GenericEntity(const string &json);

        /*!
         *  @brief  Constructs an empty GenericEntity object.
         *
         *  @since  0.100.0
         */
        explicit GenericEntity();

        virtual bool valid() const override;
    };

protected:
    inline static const string strtime
        (const system_clock::time_point &timepoint,
         const string &format, const bool &utc);
};

/*!
 * Return type for Easy calls, with an Easy::GenericEntity.
 * @since  0.100.0
 */
typedef struct return_entity : return_base
{
    Easy::GenericEntity entity;

    return_entity();
    return_entity(const uint8_t ec, const string &em,
                  const Easy::GenericEntity &ent);
} return_entity;

/*!
 * Return type for Easy calls, with a vector of Easy::GenericEntity.
 * @since  0.100.0
 */
typedef struct return_entity_vector : return_base
{
    vector<Easy::GenericEntity> entities;

    return_entity_vector();
    return_entity_vector(const uint8_t ec, const string &em,
                  const vector<Easy::GenericEntity> &vec);
} return_entity_vector;
}

#endif  // MASTODON_EASY_CPP_HPP
