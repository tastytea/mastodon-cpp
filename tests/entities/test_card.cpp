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
#include <catch.hpp>
#include "easy/entities/card.hpp"

using std::string;

using namespace Mastodon;

SCENARIO ("Easy::Card works as intended", "[entity]")
{
    GIVEN ("An Easy::Card object")
    {
        Easy::Card card;
        bool exception = false;

        WHEN ("It is initialized with valid attachment data")
        {
            const string data =
                "{\"url\":\"https://example.com/coolstuff\","
                "\"title\":\"cool stuff\","
                "\"description\":\"Very cool stuff.\","
                "\"type\":\"link\","
                "\"author_name\":\"\","
                "\"author_url\":\"\","
                "\"provider_name\":\"\","
                "\"provider_url\":\"\","
                "\"html\":\"\","
                "\"width\":400,"
                "\"height\":300,"
                "\"image\":\"https://example.com/image.png\","
                "\"embed_url\":\"\"}";

            try
            {
                card.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Card is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(card.valid());

                REQUIRE(card.url() == "https://example.com/coolstuff");
                REQUIRE(card.title() == "cool stuff");
                REQUIRE(card.description() == "Very cool stuff.");
                REQUIRE(card.type()
                        == Easy::card_type::Link);
                REQUIRE(card.author_name() == "");
                REQUIRE(card.author_url() == "");
                REQUIRE(card.provider_name() == "");
                REQUIRE(card.provider_url() == "");
                REQUIRE(card.html() == "");
                REQUIRE(card.width() == 400);
                REQUIRE(card.height() == 300);
                REQUIRE(card.image() == "https://example.com/image.png");
                REQUIRE(card.embed_url() == "");
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                card.from_string("");
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
                REQUIRE_FALSE(card.valid());
                REQUIRE(card.url() == "");
            }
        }
    }
}
