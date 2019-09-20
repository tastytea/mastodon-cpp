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
#include "easy/entities/conversation.hpp"
#include "../environment_variables.hpp"

using namespace Mastodon;

SCENARIO ("/api/v1/conversations can be called successfully",
          "[api][auth][mastodon][glitch-soc]")
{
    REQUIRE (access_token != nullptr);

    GIVEN ("instance = " + instance)
    {
        Mastodon::Easy::API masto(instance, access_token);
        return_call ret;
        Easy::Conversation conversation;
        bool exception = false;

        WHEN ("GET /api/v1/conversations is called")
        {
            try
            {
                ret = masto.get(API::v1::conversations, {{ "limit", { "2" }}});
                if (ret.answer == "[]")
                {
                    WARN("No Conversations found.");
                }
                else
                {
                    conversation.from_string(
                        Easy::json_array_to_vector(ret.answer).front());
                }
            }
            catch (const std::exception &e)
            {
                exception = true;
                WARN(e.what());
            }

            THEN("No exception is thrown")
                AND_THEN ("No error is returned")
                AND_THEN ("Answer is valid")
            {
                REQUIRE_FALSE(exception);

                REQUIRE(ret.error_code == 0);
                REQUIRE(ret.http_error_code == 200);
                REQUIRE(conversation.valid());
                REQUIRE(conversation.id() != "");
            }
        }
    }
}

