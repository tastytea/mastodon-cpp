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
#include "easy/entities/instance.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Instance works as intended", "[entity]")
{
    GIVEN ("An Easy::Instance object")
    {
        Easy::Instance instance;
        bool exception = false;

        WHEN ("It is initialized with valid instance data")
        {
            const string data =
                "{\"version\":\"2.6.5 (compatible; SuperSoftware 0.0.1)\","
                "\"urls\":{\"streaming_api\":\"wss://example.com\"},"
                "\"uri\":\"https://example.com\","
                "\"title\":\"example.com\","
                "\"thumbnail\":\"https://example.com/instance/thumbnail.jpeg\","
                "\"stats\":"
                  "{\"user_count\":3,\"status_count\":50,\"domain_count\":171},"
                "\"registrations\":null,"
                "\"max_toot_chars\":4096,"
                "\"languages\":[\"en\"],"
                "\"email\":\"admin@example.com\","
                "\"description\":\"Good instance.\"}";

            try
            {
                instance.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Instance is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(instance.valid());
                REQUIRE(instance.version()
                        == "2.6.5 (compatible; SuperSoftware 0.0.1)");
                REQUIRE(instance.urls().streaming_api == "wss://example.com");
                REQUIRE(instance.uri() == "https://example.com");
                REQUIRE(instance.title() == "example.com");
                REQUIRE(instance.thumbnail()
                        == "https://example.com/instance/thumbnail.jpeg");
                REQUIRE(instance.stats().user_count == 3);
                REQUIRE(instance.languages().front() == "en");
                REQUIRE(instance.email() == "admin@example.com");
                REQUIRE(instance.description() == "Good instance.");
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                instance.from_string("");
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("It is not valid")
                AND_THEN ("version is empty")
            {
                REQUIRE_FALSE(exception);
                REQUIRE_FALSE(instance.valid());
                REQUIRE(instance.version() == "");
            }
        }
    }
}
