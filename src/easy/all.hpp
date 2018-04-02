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
    #include "easy/easy.hpp"
    #include "easy/entities/account.hpp"
    #include "easy/entities/application.hpp"
    #include "easy/entities/attachment.hpp"
    #include "easy/entities/card.hpp"
    #include "easy/entities/context.hpp"
    #include "easy/entities/emoji.hpp"
    #include "easy/entities/instance.hpp"
    #include "easy/entities/list.hpp"
    #include "easy/entities/mention.hpp"
    #include "easy/entities/notification.hpp"
    #include "easy/entities/relationship.hpp"
    #include "easy/entities/report.hpp"
    #include "easy/entities/results.hpp"
    #include "easy/entities/status.hpp"
    #include "easy/entities/tag.hpp"
#else
    #include <mastodon-cpp/easy/easy.hpp>
    #include <mastodon-cpp/entities/easy/account.hpp>
    #include <mastodon-cpp/entities/easy/application.hpp>
    #include <mastodon-cpp/entities/easy/attachment.hpp>
    #include <mastodon-cpp/entities/easy/card.hpp>
    #include <mastodon-cpp/entities/easy/context.hpp>
    #include <mastodon-cpp/entities/easy/emoji.hpp>
    #include <mastodon-cpp/entities/easy/instance.hpp>
    #include <mastodon-cpp/entities/easy/list.hpp>
    #include <mastodon-cpp/entities/easy/mention.hpp>
    #include <mastodon-cpp/entities/easy/notification.hpp>
    #include <mastodon-cpp/entities/easy/relationship.hpp>
    #include <mastodon-cpp/entities/easy/report.hpp>
    #include <mastodon-cpp/entities/easy/results.hpp>
    #include <mastodon-cpp/entities/easy/status.hpp>
    #include <mastodon-cpp/entities/easy/tag.hpp>
#endif

#endif  // MASTODON_CPP_EASY_ALL_HPP
