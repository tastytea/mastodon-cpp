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
#include <jsoncpp/json/json.h>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using std::string;

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
     *  @brief  Describes the card type
     */
    enum class card_type
    {
        link,
        photo,
        video,
        rich,
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
     *  @brief  Base class for entities.
     */
    class Entity
    {
    public:
        explicit Entity(const string &json);

        /*!
         *  @brief  Returns true if the Entity holds valid data
         */
        const bool valid() const;

    protected:
        Json::Value _tree;
        bool _valid;
    };

    class Account;
    class Attachment;
    class Card;
};
}

#endif  // MASTODON_EASY_CPP_HPP
