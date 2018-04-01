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

#ifndef MASTODON_CPP_EASY_STATUS_HPP
#define MASTODON_CPP_EASY_STATUS_HPP

#include <string>
#include <cstdint>
#include <chrono>
#include <vector>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/easy.hpp"
    #include "easy/account.hpp"
    #include "easy/emoji.hpp"
    #include "easy/attachment.hpp"
    #include "easy/mention.hpp"
    #include "easy/tag.hpp"
    #include "easy/application.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/easy.hpp>
    #include <mastodon-cpp/easy/account.hpp>
    #include <mastodon-cpp/easy/emoji.hpp>
    #include <mastodon-cpp/easy/attachment.hpp>
    #include <mastodon-cpp/easy/mention.hpp>
    #include <mastodon-cpp/easy/tag.hpp>
    #include <mastodon-cpp/easy/application.hpp>
#endif

using std::string;
using std::uint_fast64_t;
using std::chrono::system_clock;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold statuses
     */
    class Easy::Status : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs a Status object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Status(const string &json);

        /*!
         *  @brief  Constructs an empty Status object.
         */
        Status();

        /*!
         *  @brief  Returns an array of matched accounts
         */
        const Account account() const;

        /*!
         *  @brief  Returns application from which the status was posted
         */
        const Application application() const;

        /*!
         *  @brief  Returns time of creation
         */
        const system_clock::time_point created_at() const;

        /*!
         *  @brief  Returns content of status
         */
        const string content() const;

        /*!
         *  @brief  Returns an array of emojis
         */
        const std::vector<Emoji> emojis() const;

        /*!
         *  @brief  Returns true if the user has favourited the status
         */
        const bool favourited() const;

        /*!
         *  @brief  Returns the number of favourites
         */
        const uint_fast64_t favourites_count() const;

        /*!
         *  @brief  Returns the ID of the status
         */
        const uint_fast64_t id() const;

        /*!
         *  @brief  Returns the ID of the status it replies to
         */
        const uint_fast64_t in_reply_to_id() const;

        /*!
         *  @brief  Returns the ID of the account it replies to
         */
        const uint_fast64_t in_reply_to_account_id() const;

        /*!
         *  @brief  Returns the language of the status
         */
        const string language() const;

        /*!
         *  @brief  Returns the attachments
         */
        const std::vector<Attachment> media_attachments() const;

        /*!
         *  @brief  Returns the mentions
         */
        const std::vector<Mention> mentions() const;

        /*!
         *  @brief  Returns true if the user muted the conversation
         */
        const bool muted() const;

        /*!
         *  @brief  Returns true if the status is pinned
         */
        const bool pinned() const;

        /*!
         *  @brief  Returns the reblogged Status
         */
        const Status reblog() const;

        /*!
         *  @brief  Returns true if the user has reblogged the status
         */
        const bool reblogged() const;

        /*!
         *  @brief  Returns the number of reblogs for the status
         */
        const uint_fast64_t reblogs_count() const;

        /*!
         *  @brief  Returns true if the attachments should be hidden by default
         */
        const bool sensitive() const;

        /*!
         *  @brief  Returns the spoiler text
         */
        const string spoiler_text() const;

        /*!
         *  @brief  Returns the tags
         */
        const std::vector<Tag> tags() const;

        /*!
         *  @brief  Returns the Fediverse-unique resource ID
         */
        const string uri() const;

        /*!
         *  @brief  Returns the URL to the status page
         */
        const string url() const;

        /*!
         *  @brief  Returns the visibility of the status
         */
        const visibility_type visibility() const;

        /*!
         *  @brief  Returns the 
         */

    };
}

#endif  // MASTODON_CPP_EASY_STATUS_HPP
