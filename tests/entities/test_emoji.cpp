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
#include <catch.hpp>
#include "easy/entities/emoji.hpp"
#include "easy/easy.hpp"

using std::string;

using namespace Mastodon;

SCENARIO ("Easy::Emoji works as intended", "[entity]")
{
    GIVEN ("An Easy::Emoji object")
    {
        Easy::Emoji emoji;
        bool exception = false;

        WHEN ("It is initialized with valid emoji data")
        {
            const string url
                = "https://likeable.space/emoji/custom/flower/flow.png";
            const string data =
                "[{\"shortcode\":\"flow\","
                "\"visible_in_picker\":false,"
                "\"static_url\":\"" + url + "\","
                "\"url\" : \"" + url + "\"}]";

            try
            {
                emoji.from_string(Easy::json_array_to_vector(data).front());
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Emoji is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(emoji.valid());
                REQUIRE(emoji.shortcode() == "flow");
                REQUIRE(emoji.visible_in_picker() == false);
                REQUIRE(emoji.static_url() == url);
                REQUIRE(emoji.url() == url);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                emoji.from_string("");
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("It is not valid")
                AND_THEN ("shortcode is empty")
            {
                REQUIRE_FALSE(exception);
                REQUIRE_FALSE(emoji.valid());
                REQUIRE(emoji.shortcode() == "");
            }
        }
    }
}
