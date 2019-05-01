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
#include "easy/entities/account.hpp"

using std::string;

SCENARIO ("Easy::Account works as intended", "[entity]")
{
    GIVEN ("An Easy::Account object")
    {
        Mastodon::Easy::Account account;
        bool exception = false;

        WHEN ("It is initialized with valid account data")
        {
            const string data =
                "{\"username\":\"testaccount\","
                "\"url\":\"https://example.com/users/testaccount\","
                "\"statuses_count\":2,"
                "\"source\":{"
                    "\"sensitive\":false,"
                    "\"privacy\":\"public\","
                    "\"pleroma\":{"
                        "\"show_role\":false,"
                        "\"no_rich_text\":false},"
                    "\"fields\":[],"
                    "\"note\":\"\"},"
                "\"pleroma\":{"
                    "\"tags\":[],"
                    "\"relationship\":{"
                        "\"subscribing\":false,"
                        "\"showing_reblogs\":true,"
                        "\"requested\":false,"
                        "\"muting_notifications\":false,"
                        "\"muting\":false,"
                        "\"id\":\"9hnrrVPriLiLVAhfVo\","
                        "\"following\":true,"
                        "\"followed_by\":true,"
                        "\"endorsed\":false,"
                        "\"domain_blocking\":false,"
                        "\"blocking\":false},"
                    "\"notification_settings\":{"
                        "\"remote\":true,"
                        "\"local\":true,"
                        "\"follows\":true,"
                        "\"followers\":true},"
                    "\"is_moderator\":false,"
                    "\"is_admin\":false,"
                    "\"hide_follows\":true,"
                    "\"hide_followers\":true,"
                    "\"hide_favorites\":true,"
                    "\"confirmation_pending\":false}"
                ",\"note\":\"This is a test.\","
                "\"locked\":false,"
                "\"id\":\"9hnrrVPriLiLVAhfVo\","
                "\"header_static\":\"https://example.com/images/banner.png\","
                "\"header\":\"https://example.com/images/banner.png\","
                "\"following_count\":1,"
                "\"followers_count\":1,"
                "\"fields\":[],"
                "\"emojis\":[],"
                "\"display_name\":\"testaccount\","
                "\"created_at\":\"2000-02-20T20:20:20.000Z\","
                "\"bot\":false,"
                "\"avatar_static\":\"https://example.com/images/avi.png\","
                "\"avatar\":\"https://example.com/images/avi.png\","
                "\"acct\":\"testaccount\"}";

            try
            {
                account.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Account is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(account.valid());

                REQUIRE(account.acct() == "testaccount");
                REQUIRE(account.avatar()
                        == "https://example.com/images/avi.png");
                REQUIRE(account.avatar_static()
                        == "https://example.com/images/avi.png");
                REQUIRE(!account.bot());
                REQUIRE(account.created_at().strtime("%Y_%H", false)
                        == "2000_20");
                REQUIRE(account.display_name() == "testaccount");
                REQUIRE(account.emojis().size() == 0);
                REQUIRE(account.fields().size() == 0);
                REQUIRE(account.followers_count() == 1);
                REQUIRE(account.following_count() == 1);
                REQUIRE(account.header()
                        == "https://example.com/images/banner.png");
                REQUIRE(account.header_static()
                        == "https://example.com/images/banner.png");
                REQUIRE(account.id() == "9hnrrVPriLiLVAhfVo");
                REQUIRE(account.locked() == false);
                REQUIRE(account.has_moved() == false);
                REQUIRE(!account.moved().valid());
                REQUIRE(account.note() == "This is a test.");
                REQUIRE(account.privacy()
                        == Mastodon::Easy::visibility_type::Undefined);
                REQUIRE(account.sensitive() == false);
                REQUIRE(account.source().valid());
                REQUIRE(account.source().fields().size() == 0);
                REQUIRE(account.source().language() == "");
                REQUIRE(account.source().note() == "");
                REQUIRE(account.source().privacy()
                        == Mastodon::Easy::visibility_type::Public);
                REQUIRE(!account.source().sensitive());
                REQUIRE(account.statuses_count() == 2);
                REQUIRE(account.url()
                        == "https://example.com/users/testaccount");
                REQUIRE(account.username() == "testaccount");
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                account.from_string("");
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
                REQUIRE_FALSE(account.valid());
                REQUIRE(account.id() == "");
            }
        }
    }
}
