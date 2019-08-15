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
#include "easy/entities/mention.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Mention works as intended", "[entity]")
{
    GIVEN ("An Easy::Mention object")
    {
        Easy::Mention mention;
        bool exception = false;

        WHEN ("It is initialized with valid mention data")
        {
            const string data =
                "{\"acct\" : \"testaccount\","
                "\"url\" : \"https://likeable.space/users/testaccount\","
                " \"username\" : \"testaccount\","
                " \"id\" : \"9fQhcoI95ZdmNasg0e\"}";

            try
            {
                mention.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Mention is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(mention.valid());
                REQUIRE(mention.id() == "9fQhcoI95ZdmNasg0e");
                REQUIRE(mention.acct() == "testaccount");
                REQUIRE(mention.username() == "testaccount");
                REQUIRE(mention.url() ==
                        "https://likeable.space/users/testaccount");
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                mention.from_string("");
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
                REQUIRE_FALSE(mention.valid());
                REQUIRE(mention.id() == "");
            }
        }
    }
}
