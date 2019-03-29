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

#ifndef MASTODON_CPP_EASY_CARD_HPP
#define MASTODON_CPP_EASY_CARD_HPP

#include <string>
#include <cstdint>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/easy.hpp"
    #include "easy/entity.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/easy.hpp>
    #include <mastodon-cpp/easy/entity.hpp>
#endif

using std::string;
using std::uint64_t;

namespace Mastodon
{
namespace Easy
{
    /*!
     *  @brief  Class to hold cards
     *
     *  @since before 0.11.0
     */
    class Card : public Entity
    {
    public:
        using Entity::Entity;

        virtual bool valid() const;

        /*!
         *  @brief  Returns the name of the author
         *
         *  @since before 0.11.0
         */
        const string author_name() const;

        /*!
         *  @brief  Returns the URL of the author
         *
         *  @since before 0.11.0
         */
        const string author_url() const;

        /*!
         *  @brief  Returns the description
         *
         *  @since before 0.11.0
         */
        const string description() const;

        /*!
         *  @brief  Returns the height of the card
         *
         *  @since before 0.11.0
         */
        uint64_t height() const;

        /*!
         *  @brief  Returns the HTML
         *
         *  @since before 0.11.0
         */
        const string html() const;

        /*!
         *  @brief  Returns the URL of the image associated with the card
         *
         *  @since before 0.11.0
         */
        const string image() const;

        /*!
         *  @brief  Returns the name of the provider
         *
         *  @since before 0.11.0
         */
        const string provider_name() const;

        /*!
         *  @brief  Returns the URL of the provider
         *
         *  @since before 0.11.0
         */
        const string provider_url() const;

        /*!
         *  @brief  Returns the title
         *
         *  @since before 0.11.0
         */
        const string title() const;

        /*!
         *  @brief  Returns the type of the card
         *
         *  @since before 0.11.0
         */
        Easy::card_type type() const;

        /*!
         *  @brief  Returns the URL associated with the card
         *
         *  @since before 0.11.0
         */
        const string url() const;

        /*!
         *  @brief  Returns the width of the card
         *
         *  @since before 0.11.0
         */
        uint64_t width() const;
    };
}
}

#endif  // MASTODON_CPP_EASY_CARD_HPP
