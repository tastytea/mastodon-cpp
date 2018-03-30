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

#ifndef MASTODON_CPP_EASY_ALL_HPP
#define MASTODON_CPP_EASY_ALL_HPP

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "easy.hpp"
    #include "easy/account.hpp"
    #include "easy/attachment.hpp"
    #include "easy/card.hpp"
    //#include "easy/context.hpp"
    #include "easy/emoji.hpp"
    #include "easy/instance.hpp"
    #include "easy/list.hpp"
    #include "easy/mention.hpp"
    //#include "easy/notification.hpp"
#else
    #include <mastodon-cpp/easy.hpp>
    #include <mastodon-cpp/easy/account.hpp>
    #include <mastodon-cpp/easy/attachment.hpp>
    #include <mastodon-cpp/easy/card.hpp>
    //#include <mastodon-cpp/easy/context.hpp>
    #include <mastodon-cpp/easy/emoji.hpp>
    #include <mastodon-cpp/easy/instance.hpp>
    #include <mastodon-cpp/easy/list.hpp>
    #include <mastodon-cpp/easy/mention.hpp>
    //#include <mastodon-cpp/easy/notification.hpp>
#endif

#endif  // MASTODON_CPP_EASY_ALL_HPP
