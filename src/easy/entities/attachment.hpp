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

#ifndef MASTODON_CPP_EASY_ATTACHMENT_HPP
#define MASTODON_CPP_EASY_ATTACHMENT_HPP

#include <string>
#include <cstdint>
#include <chrono>
#include <array>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"

using std::string;
using std::uint64_t;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold attachments
     *
     *  @since before 0.11.0
     */
    class Attachment : public Entity
    {
    public:
        using Entity::Entity;

        /*!
         *  @brief  Metadata for attachments.
         *
         *  @since  0.106.0
         */
        class Meta : public Entity
        {
        public:
            using Entity::Entity;

            virtual bool valid() const override;

            /*!
             *  @brief  Aspect of original image.
             *
             *  @since  0.106.0
             */
            double aspect() const;

            /*!
             *  @brief  Aspect of preview image.
             *
             *  @since  0.106.0
             */
            double aspect_small() const;

            /*!
             *  @brief  Returns the bitrate of a video.
             *
             *  @since  0.106.0
             */
            uint64_t bitrate() const;

            /*!
             *  @brief  Returns the duration of a video in seconds.
             *
             *  @since  0.106.0
             */
            const std::chrono::duration<double> duration() const;

            /*!
             *  @brief  Returns the framerate of a video in frames per second.
             *
             *  @since  0.106.0
             */
            double frame_rate() const;

            /*!
             *  @brief  Returns the height of the original image.
             *
             *  @since  0.106.0
             */
            uint64_t height() const;

            /*!
             *  @brief  Returns the height of the preview image.
             *
             *  @since  0.106.0
             */
            uint64_t height_small() const;

            /*!
             *  @brief  Returns the size of the original image.
             *
             *  @since  0.106.0
             */
            const string size() const;

            /*!
             *  @brief  Returns the size of the preview image.
             *
             *  @since  0.106.0
             */
            const string size_small() const;

            /*!
             *  @brief  Returns the width of the original image.
             *
             *  @since  0.106.0
             */
            uint64_t width() const;

            /*!
             *  @brief  Returns the width of the preview image
             *
             *  @since  0.106.0
             */
            uint64_t width_small() const;
        };

        virtual bool valid() const override;

        /*!
         *  @brief  Returns the image description
         *
         *  @since before 0.11.0
         */
        const string description() const;

        /*!
         *  @brief  Sets the image description
         *
         *  @since  0.17.0
         */
        Attachment description(const string &description);

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
         *
         *  @since before 0.11.0
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
         *  @brief  Returns the ID of the attachment
         *
         *  @since before 0.11.0
         */
        const string id() const;

        /*!
         *  @brief  Returns metadata about the attachment.
         *
         *  @since  0.106.0
         */
        const Meta meta() const;

        /*!
         *  @brief  Returns the URL of the preview image
         *
         *  @since before 0.11.0
         */
        const string preview_url() const;

        /*!
         *  @brief  Returns the remote URL of the original image
         *
         *  @since before 0.11.0
         */
        const string remote_url() const;

        /*!
         *  @brief  Returns shorter URL for the image
         *
         *  @since before 0.11.0
         */
        const string text_url() const;

        /*!
         *  @brief  Returns attachment type
         *
         *  @since before 0.11.0
         */
        attachment_type type() const;

        /*!
         *  @brief  Returns URL of the locally hosted version of the image
         *
         *  @since before 0.11.0
         */
        const string url() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_ATTACHMENT_HPP
