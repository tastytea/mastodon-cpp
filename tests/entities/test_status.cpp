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
#include "easy/entities/status.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Status works as intended", "[entity]")
{
    GIVEN ("An Easy::Status object")
    {
        Easy::Status status;
        bool exception = false;

        WHEN ("It is initialized with valid status data")
        {
            const string data =
                "{\"account\":"
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
                  "\"acct\":\"testaccount\"},"
                "\"application\":{\"name\":\"Web\",\"website\":null},"
                "\"bookmarked\":false,\"card\":null,"
                "\"content\":\"This is another test-post.\","
                "\"created_at\":\"2019-04-18T23:45:19.000Z\","
                "\"emojis\":[],\"favourited\":false,"
                "\"favourites_count\":0,\"id\":\"9hwnuJMq3eTdO4s1PU\","
                "\"in_reply_to_account_id\":null,\"in_reply_to_id\":null,"
                "\"media_attachments\":["
                  "{\"description\":\"debian.svg\",\"id\":\"-2062709746\","
                  "\"preview_url\":\"https://example.com/media/debian.svg\","
                  "\"remote_url\":\"https://example.com/media/debian.svg\","
                  "\"text_url\":\"https://example.com/media/debian.svg\","
                  "\"type\":\"unknown\","
                  "\"url\":\"https://example.com/media/debian.svg\"],"
                ",\"mentions\":[],"
                ",\"muted\":false,\"pinned\":false,"
                "\"poll\":null,\"reblog\":null,\"reblogged\":false,"
                "\"reblogs_count\":0,\"replies_count\":0,"
                "\"sensitive\":false,\"spoiler_text\":\"Test\","
                "\"tags\":[],\"uri\":\"https://example.com/objects/0000\","
                "\"url\":\"https://example.com/notice/0000\","
                "\"visibility\":\"unlisted\"}"
                ;

            try
            {
                status.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Status is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(status.valid());
                REQUIRE(status.account().id() == "9hnrrVPriLiLVAhfVo");
                REQUIRE(status.content = "This is another test-post.");
                REQUIRE(status.visibility() == Easy::visibility_type::Unlisted);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                status.from_string("");
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
                REQUIRE_FALSE(status.valid());
                REQUIRE(status.id() == "");
            }
        }
    }
}
