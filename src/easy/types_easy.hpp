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

#ifndef MASTODON_CPP_EASY_TYPES_EASY_HPP
#define MASTODON_CPP_EASY_TYPES_EASY_HPP

#include <string>
#include <utility>
#include <chrono>
#include <vector>

using std::string;
using std::chrono::system_clock;
using std::vector;

namespace Mastodon
{
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
        Error,
        Undefined
    };

    /*!
     *  @brief  Describes visibility of toots.
     *
     *  @since  before 0.11.0
     */
    // TODO: What about instance-only?
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
    // TODO: Look up what Pleroma returns.
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
     *  @since  0.100.0
     */
    typedef struct stream_event
    {
        event_type type = event_type::Undefined;
        string data;
    } stream_event;

    /*!
     *  @brief  Type of notification and 'push is requested or not'.
     *
     *  @since  0.100.0
     */
    typedef struct alert_type
    {
        Easy::notification_type type = Easy::notification_type::Undefined;
        bool pushreq = false;
    } alert_type;

    /*!
     *  @brief  Vector of Easy::alert_type.
     *
     *          Used in PushSubscription::alerts().
     *
     *  @since  0.100.0
     */
    typedef vector<alert_type> alerts;

    /*!
     *  @brief  Type for time. Converts to time_point and string.
     *
     *  @since  0.100.0
     */
    struct time
    {
        system_clock::time_point timepoint = system_clock::time_point();

        operator const system_clock::time_point() const;

        /*!
         *  @brief  Returns local time as string in ISO 8601 format (%FT%T%z).
         *
         *  @since  0.100.0
         */
        operator const string() const;

        /*!
         *  @brief  Returns local time as string in ISO 8601 format (%FT%T%z).
         *
         *  @since  0.100.0
         */
        friend std::ostream &operator <<(std::ostream &out,
                                         const Easy::time &t);

        /*!
         *  @brief  Converts time to a string.
         *
         *          The return value can not exceed 1023 chars.
         *
         *  @param  format     The format of the string, same as with
         *                     `strftime`.
         *  @param  local      Use local time (default) or UTC.
         *
         *  Example:
         *  @code
         *  Mastodon::Easy::time timepoint = status.created_at();
         *  std::cout << timepoint.strtime("%F, %T UTC", false) << '\n';
         *  @endcode
         *
         *  @return The time as string.
         *
         *  @since  0.100.0
         */
        const string strtime(const string &format,
                             const bool &local = true) const;
    };
}
}
#endif  // MASTODON_CPP_EASY_TYPES_EASY_HPP
