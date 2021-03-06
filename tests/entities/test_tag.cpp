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
#include "easy/entities/tag.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Tag works as intended", "[entity]")
{
    GIVEN ("An Easy::Tag object")
    {
        Easy::Tag tag;
        bool exception = false;

        WHEN ("It is initialized with valid tag data")
        {
            const string data =
                "{\"name\":\"testtag\","
                "\"url\":\"https://example.com/tag/testtag\","
                "\"history\":"
                  "[{\"day\":\"1565579400\",\"uses\":4,\"accounts\":2}]}";

            try
            {
                tag.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Tag are valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(tag.valid());
                REQUIRE(tag.name() == "testtag");
                REQUIRE(tag.history()[0].uses() == 4);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                tag.from_string("");
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("It is not valid")
                AND_THEN ("history is empty")
            {
                REQUIRE_FALSE(exception);
                REQUIRE_FALSE(tag.valid());
                REQUIRE(tag.history().size() == 0);
            }
        }
    }
}
