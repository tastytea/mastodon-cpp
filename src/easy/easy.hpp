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
#include <array>
#include <jsoncpp/json/json.h>
// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using std::string;
using std::uint16_t;
using std::uint64_t;

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
     *  @brief  Class to hold accounts.
     */
    class Account
    {
    public:
        /*!
         *  @brief  Constructs an Account object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Account(const string &json);

        /*!
         *  @brief  Returns true if the account holds valid data
         */
        const bool valid() const;

        /*!
         *  @brief  Returns username
         *
         *          `username` for users on the same instance, `user@hostname`
         *          for users on other instances.
         */
        const string acct() const;

        /*!
         *  @brief  Returns URL of avatar
         */
        const string avatar() const;

        /*!
         *  @brief  Returns URL of static avatar
         */
        const string avatar_static() const;

        /*!
         *  @brief  Returns time of creation
         */
        const std::chrono::system_clock::time_point created_at() const;

        /*!
         *  @brief  Returns display name
         */
        const string display_name() const;

        /*!
         *  @brief  Returns number of followers
         */
        const uint64_t followers_count() const;

        /*!
         *  @brief  Returns number of people this account follows
         */
        const uint64_t following_count() const;

        /*!
         *  @brief  Returns URL of header image
         */
        const string header() const;

        /*!
         *  @brief  Returns URL of static header image
         */
        const string header_static() const;

        /*!
         *  @brief  Returns account-ID
         */
        const uint64_t id() const;

        /*!
         *  @brief  Returns true if the account is locked
         */
        const bool locked() const;

        /*!
         *  @brief  Returns true if the account has been moved
         */
        const bool has_moved() const;

        /*!
         *  @brief  If the owner decided to switch accounts, new account is in
         *          this attribute
         */
        const Account moved() const;

        /*!
         *  @brief  Returns note
         */
        const string note() const;

        /*!
         *  @brief  Returns plaintext version of note
         */
        const string note_plain() const;

        /*!
         *  @brief  Returns default privacy of new toots
         */
        const visibility privacy() const;

        /*!
         *  @brief  Returns if media is marked as sensitive by default
         */
        const bool sensitive() const;

        /*!
         *  @brief  Returns number of statuses
         */
        const uint64_t statuses_count() const;

        /*!
         *  @brief  Returns URL of the profile
         */
        const string url() const;

        /*!
         *  @brief  Returns username (without @hostname)
         */
        const string username() const;

    private:
        Json::Value _tree;
        bool _valid;
    };

    /*!
     *  @brief  Class to hold attachments
     */
    class Attachment
    {
    public:
        /*!
         *  @brief  Constructs an Attachment object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Attachment(const string &json);

        /*!
         *  @brief  Returns true if the attachment holds valid data
         */
        const bool valid() const;

        /*!
         *  @brief  Aspect of original image
         */
        const double aspect() const;

        /*!
         *  @brief  Aspect of preview image
         */
        const double aspect_small() const;

        /*!
         *  @brief  Returns the image description
         */
        const string description() const;

        /*!
         *  @brief  Returns the focus point (x, y)
         */
        // TODO: find attachment with focus
        const std::array<uint64_t, 2> focus() const;

        /*!
         *  @brief  Returns the height of the original image
         */
        const uint64_t height() const;

        /*!
         *  @brief  Returns the height of the preview image
         */
        const uint64_t height_small() const;

        /*!
         *  @brief  Returns the ID of the attachment
         */
        const uint64_t id() const;

        /*!
         *  @brief  Returns the URL of the preview image
         */
        const string preview_url() const;

        /*!
         *  @brief  Returns the remote URL of the original image
         */
        const string remote_url() const;

        /*!
         *  @brief  Returns the size of the original image
         */
        const string size() const;

        /*!
         *  @brief  Returns the size of the preview image
         */
        const string size_small() const;

        /*!
         *  @brief  Returns shorter URL for the image
         */
        const string text_url() const;

        /*!
         *  @brief  Returns attachment type
         */
        const attachment_type type() const;

        /*!
         *  @brief  Returns URL of the locally hosted version of the image
         */
        const string url() const;

        /*!
         *  @brief  Returns the width of the original image
         */
        const uint64_t width() const;

        /*!
         *  @brief  Returns the width of the preview image
         */
        const uint64_t width_small() const;


        // TODO: find an attachment with framerate, duration or bitrate set
        // const uint16_t framerate() const;
        // const std::chrono::seconds duration() const;
        // const uint64_t bitrate() const;

    private:
        Json::Value _tree;
        bool _valid;
    };

    /*!
     *  @brief  Class to hold cards
     */
    class Card
    {
    public:
        /*!
         *  @brief  Constructs a Card object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Card(const string &json);

        /*!
         *  @brief  Returns true if the card holds valid data
         */
        const bool valid() const;

        const string url() const;
        const string title() const;
        const string description() const;
        const string image() const;
        const string type() const;
        const string author_name() const;
        const string author_url() const;
        const string provider_name() const;
        const string provider_url() const;
        const string html() const;
        const string width() const;
        const string height() const;

    private:
        Json::Value _tree;
        bool _valid;
    };
};
}

#endif  // MASTODON_EASY_CPP_HPP
