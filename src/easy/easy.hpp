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
#include <ostream>
#include <jsoncpp/json/json.h>
#include "return_types_easy.hpp"

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
/*!
 *  @brief  Child of Mastodon::API with abstract methods.
 *
 *  @since  before 0.11.0
 */
namespace Easy
{
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

    // TODO: Get rid of forward declarations.
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
    // TODO: Convert to struct?
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
     *  @brief  Turns a JSON array into a vector of strings
     *
     *  @param  json    JSON string holding the array
     *
     *  @return vector of strings or an empty vector on error
     *
     *  @since  before 0.11.0
     */
    const std::vector<string> json_array_to_vector(const string &json);

    /*!
     *  @brief  Split stream into a vector of events
     *
     *  @param  streamdata  Data from get_stream()
     *
     *  @return vector of stream events
     *
     *  @since  before 0.11.0
     */
    const std::vector<stream_event> parse_stream(const std::string &streamdata);

    /*!
     *  @brief  Interface to the Mastodon API, easy version.
     *
     *  Provides convenient functions to deal with the responses you get.
     */
    class API : public Mastodon::API
    {
    public:
        /*!
         *  @brief  Constructs a new Easy object.
         *
         *          To register your application, leave access_token blank and
         *          call register_app1() and register_app2().
         *
         *  @param  instance      The hostname of your instance
         *  @param  access_token  The access token
         *
         *  @since  before 0.11.0
         */
        explicit API(const string &instance, const string &access_token);

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
         *  @param  format     The format of the string, same as with
         *                     `strftime`.
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
        // TODO: Time type, convertible to time_point, str_utc and str_local.
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
        // TODO: Own file.

        /*!
         *  @brief  Sends a post.
         *
         *  @param  status  The status to send
         *  @param  error   @ref error "Error code"
         *
         *  @return The new Easy::Status
         *
         *  @since  0.18.1
         */
        const return_entity<Easy::Status> send_post(const Status &status);

        /*!
         *  @brief  Alias for send_post()
         *
         *  @since  0.17.0
         */
        const return_entity<Easy::Status> send_toot(const Status &status);

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
        const return_entity_vector<Easy::Notification> get_notifications(
            const uint16_t limit = 20, const string since_id = "",
            const string max_id = "");

    protected:
        inline static const string strtime
        (const system_clock::time_point &timepoint,
         const string &format, const bool &utc);
};
}
}

#endif  // MASTODON_EASY_CPP_HPP
