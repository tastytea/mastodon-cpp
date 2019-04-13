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
#include <vector>
#include <functional>
#include <ostream>
#include <jsoncpp/json/json.h>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/return_types_easy.hpp"
    #include "easy/types_easy.hpp"
    #include "easy/entities/notification.hpp"
    #include "easy/entities/status.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/return_types_easy.hpp>
    #include <mastodon-cpp/easy/types_easy.hpp>
    #include <mastodon-cpp/easy/entities/notification.hpp>
    #include <mastodon-cpp/easy/entities/status.hpp>
#endif

using std::string;
using std::vector;
using std::uint64_t;
using std::uint16_t;

namespace Mastodon
{
/*!
 *  @brief  Child of Mastodon::API with abstract methods.
 *
 *  @since  before 0.100.0
 */
namespace Easy
{
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
     *  @return vector of Easy::stream_event
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
         *  @since  0.100.0
         */
        explicit API(const string &instance, const string &access_token);

        /*!
         *  @brief  Gets the links from the last answer
         *
         *  @since  0.100.0
         */
        const Link get_link() const;

        /*!
         *  @brief  Sends a post.
         *
         *  @param  status  The status to send
         *  @param  error   @ref error "Error code"
         *
         *  @return The new Easy::Status
         *
         *  @since  0.100.0
         */
        const return_entity<Easy::Status> send_post(const Status &status);

        /*!
         *  @brief  Alias for send_post()
         *
         *  @since  0.100.0
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
         *  @since  0.100.0
         */
        const return_entity_vector<Easy::Notification> get_notifications(
            const uint16_t limit = 20, const string since_id = "",
            const string max_id = "");
    };
}
}

#endif  // MASTODON_EASY_CPP_HPP
