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
#include "mastodon-cpp.hpp"
#include "easy/easy.hpp"
#include "easy/entities/poll.hpp"
#include "../environment_variables.hpp"

using namespace Mastodon;

SCENARIO ("/api/v1/polls/:id/votes can be called successfully",
          "[api][auth][mastodon][pleroma][glitch-soc]")
{
    REQUIRE (access_token != nullptr);

    GIVEN ("instance = " + instance)
    {
        Mastodon::Easy::API masto(instance, access_token);
        return_call ret;
        Easy::Poll poll;
        bool exception = false;

        WHEN ("POST /api/v1/polls/:id/votes is called")
        {
            try
            {
                ret = masto.post(API::v1::polls_id_votes,
                                 {
                                     { "id", { "4823515" } },
                                     // TODO: Check if this is the right format.
                                     { "choices", { "false", "false", "true",
                                                    "false", "false" } }
                                 });
                if (ret.answer == "[]")
                {
                    WARN("Poll not found.");
                }
                else
                {
                    poll.from_string(ret.answer);
                }
            }
            catch (const std::exception &e)
            {
                exception = true;
                WARN(e.what());
            }

            THEN("No exception is thrown")
                AND_THEN ("An error is returned")
                AND_THEN ("Answer is invalid")
            {
                REQUIRE_FALSE(exception);

                REQUIRE(ret.error_code == 12);
                REQUIRE(ret.http_error_code != 200); // Pleroma returns 422.
                REQUIRE_FALSE(poll.valid());
                REQUIRE(poll.id() == "");
                REQUIRE(poll.error() == "Poll's author can't vote");
            }
        }
    }
}

