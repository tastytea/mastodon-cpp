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

#ifndef MASTODON_CPP_EASY_ATTACHMENT_HPP
#define MASTODON_CPP_EASY_ATTACHMENT_HPP

#include <string>
#include <cstdint>
#include <chrono>
#include <array>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy.hpp>
#endif

using std::string;
using std::uint16_t;
using std::uint64_t;

namespace Mastodon
{
    /*!
     *  @brief  Class to hold attachments
     */
    class Easy::Attachment : public Easy::Entity
    {
    public:
        /*!
         *  @brief  Constructs an Attachment object from a JSON string.
         *
         *  @param  json    JSON string
         */
        explicit Attachment(const string &json);

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
    };
}

#endif  // MASTODON_CPP_EASY_ATTACHMENT_HPP
