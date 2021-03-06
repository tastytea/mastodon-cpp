/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MASTODON_CPP_EASY_STATUS_HPP
#define MASTODON_CPP_EASY_STATUS_HPP

#include <string>
#include <cstdint>
#include <vector>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"
#include "account.hpp"
#include "emoji.hpp"
#include "attachment.hpp"
#include "mention.hpp"
#include "tag.hpp"
#include "application.hpp"
#include "card.hpp"

using std::string;
using std::uint64_t;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold statuses
         *
         *  @since  before 0.11.0
     */
    class Status : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns an array of matched accounts.
         *
         *  @since  before 0.11.0
         */
        const Account account() const;

        /*!
         *  @brief  Returns application from which the status was posted.
         *
         *  @since  before 0.11.0
         */
        const Application application() const;

        /*!
         *  @brief  Returns card
         *
         *  @since  0.19.0
         */
        const Card card() const;

        /*!
         *  @brief  Returns time of creation
         *
         *  @since  before 0.11.0
         */
        const Easy::time_type created_at() const;

        /*!
         *  @brief  Returns content of status
         *
         *  @since  before 0.11.0
         */
        const string content() const;

        /*!
         *  @brief  Sets content of status
         *
         *  @since  0.17.0
         */
        Status content(const string &content);

        /*!
         *  @brief  Returns an array of emojis
         *
         *  @since  before 0.11.0
         */
        const std::vector<Emoji> emojis() const;

        /*!
         *  @brief  Returns true if the user has favourited the status
         *
         *  @since  before 0.11.0
         */
        bool favourited() const;

        /*!
         *  @brief  Returns the number of favourites
         *
         *  @since  before 0.11.0
         */
        uint64_t favourites_count() const;

        /*!
         *  @brief  Returns the ID of the status
         *
         *  @since  before 0.11.0
         */
        const string id() const;

        /*!
         *  @brief  Returns the ID of the status it replies to
         *
         *  @since  before 0.11.0
         */
        const string in_reply_to_id() const;

        /*!
         *  @brief  Sets the ID of the status it replies to
         *
         *  @since  0.17.0
         */
        Status in_reply_to_id(const string &in_reply_to_id);

        /*!
         *  @brief  Returns the ID of the account it replies to
         *
         *  @since  before 0.11.0
         */
        const string in_reply_to_account_id() const;

        /*!
         *  @brief  Returns the language of the status
         *
         *  @since  before 0.11.0
         */
        const string language() const;

        /*!
         *  @brief  Overrides the language of the status (ISO 639-2)
         *
         *  @since  0.17.0
         */
        Status language(const string &language);

        /*!
         *  @brief  Returns the attachments
         *
         *  @since  before 0.11.0
         */
        const std::vector<Attachment> media_attachments() const;

        /*!
         *  @brief  Sets the attachments
         *
         *  @since  0.17.0
         */
        Status media_attachments
            (const std::vector<Attachment> &media_attachments);

        /*!
         *  @brief  Returns the mentions
         *
         *  @since  before 0.11.0
         */
        const std::vector<Mention> mentions() const;

        /*!
         *  @brief  Returns true if the user muted the conversation
         *
         *  @since  before 0.11.0
         */
        bool muted() const;

        /*!
         *  @brief  Returns true if the status is pinned
         *
         *  @since  before 0.11.0
         */
        bool pinned() const;

        /*!
         *  @brief  Returns the reblogged Status
         *
         *  @since  before 0.11.0
         */
        const Status reblog() const;

        /*!
         *  @brief  Returns true if the user has reblogged the status
         *
         *  @since  before 0.11.0
         */
        bool reblogged() const;

        /*!
         *  @brief  Returns the number of reblogs for the status
         *
         *  @since  before 0.11.0
         */
        uint64_t reblogs_count() const;

        /*!
         *  @brief  Returns the number of replies for the status
         *
         *  @since  0.19.0
         */
        uint64_t replies_count() const;

        /*!
         *  @brief  Returns true if the attachments should be hidden by default
         *
         *  @since  before 0.11.0
         */
        bool sensitive() const;

        /*!
         *  @brief  Sets sensitive flag for attachments
         *
         *  @since  0.17.0
         */
        Status sensitive(const bool &sensitive);

        /*!
         *  @brief  Returns the spoiler text
         *
         *  @since  before 0.11.0
         */
        const string spoiler_text() const;

        /*!
         *  @brief  Sets the spoiler text
         *
         *  @since  0.17.0
         */
        Status spoiler_text(const string &spoiler_text);

        /*!
         *  @brief  Returns the tags
         *
         *  @since  before 0.11.0
         */
        const std::vector<Tag> tags() const;

        /*!
         *  @brief  Returns the Fediverse-unique resource ID
         *
         *  @since  before 0.11.0
         */
        const string uri() const;

        /*!
         *  @brief  Returns the URL to the status page
         *
         *  @since  before 0.11.0
         */
        const string url() const;

        /*!
         *  @brief  Returns the visibility of the status
         *
         *  @since  before 0.11.0
         */
        visibility_type visibility() const;

        /*!
         *  @brief  Sets the visibility of the status
         *
         *  @since  0.17.0
         */
        Status visibility(const visibility_type &visibility);
    };
}
}

#endif  // MASTODON_CPP_EASY_STATUS_HPP
