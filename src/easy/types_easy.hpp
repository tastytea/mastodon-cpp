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
#include <map>

using std::string;
using std::chrono::system_clock;

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
    typedef struct stream_event
    {
        event_type type = event_type::Undefined;
        string data;
    } stream_event;

    /*!
     *  @brief  Map of 'notification type' and 'push is requested or not'.
     *
     *          Used in PushSubscription::alerts().
     *
     *  @since  0.13.3
     */
    typedef std::map<Easy::notification_type, bool> alertmap;

    /*!
     *  @brief  Type for time. Converts to time_point and string.
     *
     *  @since  0.100.0
     */
    struct time
    {
        system_clock::time_point timepoint = system_clock::time_point();

        operator const system_clock::time_point();
        operator const string();
        friend std::ostream &operator <<(std::ostream &out,
                                         const Easy::time &t);

        /*!
         *  @brief  Converts time to a string.
         *
         *          The return value can not exceed 1023 chars.
         *
         *  @param  format     The format of the string, same as with
         *                     `strftime`.
         *  @param  local      Use local time (default).
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
        const string strtime (const string &format,
                              const bool &local = true) const;
    };
}
}
#endif  // MASTODON_CPP_EASY_TYPES_EASY_HPP
