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
#include "easy/entities/context.hpp"

using std::string;

using namespace Mastodon;

SCENARIO ("Easy::Context works as intended", "[entity]")
{
    GIVEN ("An Easy::Context object")
    {
        Easy::Context context;
        bool exception = false;

        WHEN ("It is initialized with valid context data")
        {
            const string url = "https://example.com/objects/00000000-ffff-0000-ffff-000000000000";
            const string data =
                "{\"descendants\":["
                "{\"visibility\":\"public\","
                  "\"url\":\"" + url + "\","
                  "\"uri\":\"" + url + "\","
                  "\"tags\":[],"
                  "\"spoiler_text\":\"\","
                  "\"sensitive\":false,"
                  "\"replies_count\":0,"
                  "\"reblogs_count\":0,"
                  "\"reblogged\":false,"
                  "\"reblog\":null,"
                  "\"pleroma\":{"
                    "\"spoiler_text\":{\"text/plain\":\"\"},"
                    "\"local\":false,"
                    "\"in_reply_to_account_acct\":\"testuser\","
                    "\"conversation_id\":9999999,"
                    "\"content\":{\"text/plain\":\"descendant_text\"}},"
                  "\"pinned\":false,"
                  "\"muted\":false,"
                  "\"mentions\":["
                    "{\"username\":\"testuser\","
                    "\"url\":\"https://example.com/users/testuser\","
                    "\"id\":\"9hnrrVPriLiLVAhfVo\","
                    "\"acct\":\"tastytea\"}],"
                  "\"media_attachments\":[],"
                  "\"language\":null,"
                  "\"in_reply_to_id\":\"9hwnuJMq3eTdO4s1PU\","
                  "\"in_reply_to_account_id\":\"9hnrrVPriLiLVAhfVo\","
                  "\"id\":\"9hwnuJMq3eTdO4s1PU\","
                  "\"favourites_count\":1,"
                  "\"favourited\":false,"
                  "\"emojis\":[],"
                  "\"created_at\":\"2019-05-08T11:01:01.000Z\","
                  "\"content\":\"<p>descendant_test</p>\","
                  "\"card\":null,"
                  "\"bookmarked\":false,"
                  "\"application\":{\"website\":null,\"name\":\"Web\"}}],"
                "\"ancestors\":["
                "{\"visibility\":\"public\","
                  "\"url\":\"" + url + "\","
                  "\"uri\":\"" + url + "\","
                  "\"tags\":[],"
                  "\"spoiler_text\":\"\","
                  "\"sensitive\":false,"
                  "\"replies_count\":0,"
                  "\"reblogs_count\":0,"
                  "\"reblogged\":false,"
                  "\"reblog\":null,"
                  "\"pleroma\":{"
                    "\"spoiler_text\":{\"text/plain\":\"\"},"
                    "\"local\":false,"
                    "\"in_reply_to_account_acct\":\"testuser\","
                    "\"conversation_id\":9999999,"
                    "\"content\":{\"text/plain\":\"ancestor_text\"}},"
                  "\"pinned\":false,"
                  "\"muted\":false,"
                  "\"mentions\":["
                    "{\"username\":\"testuser\","
                    "\"url\":\"https://example.com/users/testuser\","
                    "\"id\":\"9hnrrVPriLiLVAhfVo\","
                    "\"acct\":\"tastytea\"}],"
                  "\"media_attachments\":[],"
                  "\"language\":null,"
                  "\"in_reply_to_id\":\"9hwnuJMq3eTdO4s1PU\","
                  "\"in_reply_to_account_id\":\"9hnrrVPriLiLVAhfVo\","
                  "\"id\":\"9hwnuJMq3eTdO4s1PU\","
                  "\"favourites_count\":1,"
                  "\"favourited\":false,"
                  "\"emojis\":[],"
                  "\"created_at\":\"2019-05-08T11:01:01.000Z\","
                  "\"content\":\"<p>ancestor_test</p>\","
                  "\"card\":null,"
                  "\"bookmarked\":false,"
                  "\"application\":{\"website\":null,\"name\":\"Web\"}}]}";

            try
            {
                context.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Context is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(context.valid());
                REQUIRE(context.ancestors().front().url() == url);
                REQUIRE(context.descendants().front().url() == url);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                context.from_string("");
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("It is not valid")
            {
                REQUIRE_FALSE(exception);
                REQUIRE_FALSE(context.valid());
            }
        }
    }
}
