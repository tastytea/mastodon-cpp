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
#include "easy/entities/pushsubscription.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::PushSubscription works as intended", "[entity]")
{
    GIVEN ("An Easy::PushSubscription object")
    {
        Easy::PushSubscription pushsubscription;
        bool exception = false;

        WHEN ("It is initialized with valid pushsubscription data")
        {
            const string data =
                "{\"id\":\"1234\","
                "\"endpoint\":\"https://example.org/test\","
                "\"server_key\":\"1234\","
                "\"alerts\":{\"mention\":true}}";

            try
            {
                pushsubscription.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("PushSubscription is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(pushsubscription.valid());
                REQUIRE(pushsubscription.id() == "1234");
                REQUIRE(pushsubscription.endpoint() == "https://example.org/test");
                REQUIRE(pushsubscription.server_key() == "1234");
                REQUIRE(pushsubscription.alerts()[0].type == Easy::notification_type::Mention);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                pushsubscription.from_string("");
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
                REQUIRE_FALSE(pushsubscription.valid());
                REQUIRE(pushsubscription.id() == "");
            }
        }
    }
}
