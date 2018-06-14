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
    #include "easy/easy.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/easy.hpp>
#endif

using std::string;
using std::uint_fast64_t;

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
         *  @brief  Constructs an empty Attachment object.
         */
        Attachment();

        /*!
         *  @brief  Aspect of original image
         */
        const double aspect() const;

        /*!
         *  @brief  Aspect of preview image
         */
        const double aspect_small() const;

        /*!
         *  @brief  Returns the bitrate of a video
         */
        const uint_fast64_t bitrate() const;

        /*!
         *  @brief  Returns the image description
         */
        const string description() const;

        /*!
         *  @brief  Sets the image description
         *  
         *  @since  0.17.0
         */
        Attachment description(const string &description);

        /*!
         *  @brief  Returns the duration of a video in seconds
         */
        const std::chrono::duration<double> duration() const;

        /*!
         * @brief  Gets file to upload
         * 
         * @since  0.17.0
         */
        const string file() const;

        /*!
         * @brief  Sets file to upload
         * 
         * @since  0.17.0
         *
         * @param  file    Filename
         */
        Attachment file(const string &file);

        /*!
         *  @brief  Returns the focus point (x, y)
         *  
         *          Values are between -1.0 and 1.0.
         */
        const std::array<double, 2> focus() const;

        /*!
         *  @brief  Sets the focus point (x, y)
         *  
         *          Values are between -1.0 and 1.0.
         *          
         *  @since  0.17.0
         */
        Attachment focus(const std::array<double, 2> &focus);

        /*!
         *  @brief  Returns the framerate of a video in frames per second
         */
        const double framerate() const;

        /*!
         *  @brief  Returns the height of the original image
         */
        const uint_fast64_t height() const;

        /*!
         *  @brief  Returns the height of the preview image
         */
        const uint_fast64_t height_small() const;

        /*!
         *  @brief  Returns the ID of the attachment
         */
        const uint_fast64_t id() const;

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
        const uint_fast64_t width() const;

        /*!
         *  @brief  Returns the width of the preview image
         */
        const uint_fast64_t width_small() const;


    };
}

#endif  // MASTODON_CPP_EASY_ATTACHMENT_HPP
