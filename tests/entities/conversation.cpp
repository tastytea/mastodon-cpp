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
#include "easy/entities/conversation.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Conversation works as intended", "[entity]")
{
    GIVEN ("An Easy::Conversation object")
    {
        Easy::Conversation conversation;
        bool exception = false;

        WHEN ("It is initialized with valid conversation data")
        {
            const string data =
                "\"id\":\"1234567\","
                "\"accounts\":["
                  "{\"id\":\"98765\"},"
                  "{\"id\":\"56789\"}],"
                "\"last_status\":null,"
                "\"unread\":false}";

            try
            {
                conversation.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Conversation is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(conversation.valid());
                REQUIRE(conversation.id() == "1234567");
                REQUIRE(conversation.accounts().size() == 2);
                REQUIRE(conversation.unread() == false);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                conversation.from_string("");
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
                REQUIRE_FALSE(conversation.valid());
                REQUIRE(conversation.id() == "");
                REQUIRE(conversation.accounts().size() == 0);
            }
        }
    }
}
