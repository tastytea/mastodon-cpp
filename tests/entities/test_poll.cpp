/*  This file is part of mastodon-cpp.
 *  Copyright © 2019 tastytea <tastytea@tastytea.de>
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

#include <exception>
#include <string>
#include <chrono>
#include <catch.hpp>
#include "easy/entities/poll.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Poll works as intended", "[entity]")
{
    GIVEN ("An Easy::Poll object")
    {
        Easy::Poll poll;
        bool exception = false;

        WHEN ("It is initialized with valid poll data")
        {
            const string data =
                "{\"emojis\":[],"
                "\"expired\":false,"
                "\"expires_at\":\"2019-09-22T12:48:19.000Z\","
                "\"id\":\"1234567\","
                "\"multiple\":false,"
                "\"options\":["
                  "{\"title\":\"Yes\"," "\"votes_count\":12},"
                  "{\"title\":\"No\",\"votes_count\":13}],"
                "\"voted\":false,"
                "\"votes_count\":25}";

            try
            {
                poll.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Poll is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(poll.valid());
                REQUIRE(poll.id() == "1234567");
                REQUIRE(poll.expired() == false);
                REQUIRE(poll.options().size() == 2);
                REQUIRE(poll.options()[1].votes_count == 13);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                poll.from_string("");
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
                REQUIRE_FALSE(poll.valid());
                REQUIRE(poll.id() == "");
                REQUIRE(poll.options().size() == 0);
            }
        }
    }
}
