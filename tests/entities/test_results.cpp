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
#include "easy/entities/results.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Results works as intended", "[entity]")
{
    GIVEN ("An Easy::Results object")
    {
        Easy::Results results;
        bool exception = false;

        WHEN ("It is initialized with valid results data")
        {
            const string data =
                "{\"statuses\":[],\"hashtags\":[],\"accounts\":["
                "{\"username\":\"testaccount\","
                "\"url\":\"https://example.com/users/testaccount\","
                "\"statuses_count\":2,"
                "\"note\":\"This is a test.\","
                "\"locked\":false,"
                "\"id\":\"9hnrrVPriLiLVAhfVo\","
                "\"header_static\":\"https://example.com/images/banner.png\","
                "\"header\":\"https://example.com/images/banner.png\","
                "\"following_count\":1,"
                "\"followers_count\":1,"
                "\"emojis\":[],"
                "\"display_name\":\"testaccount\","
                "\"created_at\":\"2000-02-20T20:20:20.000Z\","
                "\"avatar_static\":\"https://example.com/images/avi.png\","
                "\"avatar\":\"https://example.com/images/avi.png\","
                "\"acct\":\"testaccount\"}"
                "]}";

            try
            {
                results.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Results are valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(results.valid());
                REQUIRE(results.accounts()[0].id() == "9hnrrVPriLiLVAhfVo");
                REQUIRE(results.accounts()[0].following_count() == 1);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                results.from_string("");
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("It is not valid")
                AND_THEN ("accounts is empty")
            {
                REQUIRE_FALSE(exception);
                REQUIRE_FALSE(results.valid());
                REQUIRE(results.accounts().size() == 0);
            }
        }
    }
}
