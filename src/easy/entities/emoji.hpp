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

#ifndef MASTODON_CPP_EASY_EMOJI_HPP
#define MASTODON_CPP_EASY_EMOJI_HPP

#include <string>

#include "../../mastodon-cpp.hpp"
#include "../entity.hpp"

using std::string;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold emojis.
     *
     *  @since  before 0.11.0
     */
    class Emoji : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const override;

        /*!
         *  @brief  Returns the shortcode of the emoji.
         *
         *  @since  before 0.11.0
         */
        const string shortcode() const;

        /*!
         *  @brief  Returns the URL to the emoji static image.
         *
         *  @since  before 0.11.0
         */
        const string static_url() const;

        /*!
         *  @brief  Returns the URL to the emoji image.
         *
         *  @since  before 0.11.0
         */
        const string url() const;

        /*!
         *  @brief  Returns if the emoji is visible in the picker.
         *
         *  @since  0.106.0
         */
        bool visible_in_picker() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_EMOJI_HPP
