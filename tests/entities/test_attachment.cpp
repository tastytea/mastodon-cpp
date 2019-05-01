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
#include "easy/entities/attachment.hpp"

using std::string;

using namespace Mastodon;

SCENARIO ("Easy::Attachment works as intended", "[entity]")
{
    GIVEN ("An Easy::Attachment object")
    {
        Easy::Attachment att;
        bool exception = false;

        WHEN ("It is initialized with valid attachment data")
        {
            const string url
                = "https://example.com/media/e5432f56630c1e38080d135295e33aeb"
                "ee21e28a46c2172dc010f5e06fe0bd6a.png?name=tux.png";
            const string data =
                "{\"description\" : \"tux.png\","
                "\"id\" : \"2127742613\","
                "\"pleroma\" : {"
                    "\"mime_type\" : \"image/png\"},"
                "\"preview_url\" : \"" + url + "\","
                "\"remote_url\" : \"" + url + "\","
                "\"text_url\" : \"" + url + "\","
                "\"type\" : \"image\","
                "\"url\" :"
                  "\"https://example.com/media/e5432f56630c1e38080d135295e33aeb"
                  "ee21e28a46c2172dc010f5e06fe0bd6a.png?name=tux.png\"}";

            try
            {
                att.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Attachment is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(att.valid());

                REQUIRE(att.id() == "2127742613");
                REQUIRE(att.type() == Easy::attachment_type::Image);
                REQUIRE(att.url() == url);
                REQUIRE(att.remote_url() == url);
                REQUIRE(att.preview_url() == url);
                REQUIRE(att.meta().valid());
                REQUIRE(att.description() == "tux.png");
                REQUIRE(att.meta().width() == 0);
                REQUIRE(att.meta().width_small() == 0);
                REQUIRE(att.meta().height() == 0);
                REQUIRE(att.meta().height_small() == 0);
                REQUIRE(att.meta().size() == "");
                REQUIRE(att.meta().size_small() == "");
                REQUIRE(att.meta().aspect() == 0.0);
                REQUIRE(att.meta().aspect_small() == 0.0);
                REQUIRE(att.meta().frame_rate() == 0.0);
                REQUIRE(att.meta().duration()
                        == std::chrono::duration<double>(0.0));
                REQUIRE(att.meta().bitrate() == 0);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                att.from_string("");
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
                REQUIRE_FALSE(att.valid());
                REQUIRE(att.id() == "");
            }
        }
    }
}
