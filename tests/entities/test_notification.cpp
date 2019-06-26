/*  This file is part of mastodon-cpp.
 *  Copyright © 2019 tastytea <tastytea@tastytea.de>
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

#include <exception>
#include <string>
#include <chrono>
#include <catch.hpp>
#include "easy/entities/notification.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Notification works as intended", "[entity]")
{
    GIVEN ("An Easy::Notification object")
    {
        Easy::Notification notification;
        bool exception = false;

        WHEN ("It is initialized with valid notification data")
        {
            const string data =
                "{\"id\" : \"1234\","
                "\"type\" : \"follow\","
                "\"account\" : "
                  "{\"acct\" : \"testaccount@likeable.space\"},"
                " \"created_at\" : \"2019-06-25T15:52:08.000Z\"}";

            try
            {
                notification.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Notification is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(notification.valid());
                REQUIRE(notification.id() == "1234");
                REQUIRE(notification.type() == Easy::notification_type::Follow);
                REQUIRE(notification.account().acct() ==
                        "testaccount@likeable.space");
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                notification.from_string("");
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("It is not valid")
                AND_THEN ("id is empty")
            {
                REQUIRE_FALSE(exception);
                REQUIRE_FALSE(notification.valid());
                REQUIRE(notification.id() == "");
            }
        }
    }
}
