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
#include "easy/entities/emoji.hpp"
#include "../environment_variables.hpp"

using namespace Mastodon;

SCENARIO ("/api/v1/custom_emojis can be called successfully",
          "[api][mastodon][pleroma][glitch-soc]")
{
    GIVEN ("instance = " + instance)
    {
        Mastodon::Easy::API masto(instance, "");
        return_call ret;
        Easy::Emoji emoji;
        bool exception = false;

        WHEN ("GET /api/v1/custom_emojis is called")
        {
            try
            {
                ret = masto.get(API::v1::custom_emojis);
                if (ret.answer == "[]")
                {
                    WARN("No custom emojis found.");
                }
                else
                {
                    emoji.from_string
                        (Easy::json_array_to_vector(ret.answer).front());
                }
            }
            catch (const std::exception &e)
            {
                exception = true;
                WARN(e.what());
            }

            THEN("No exception is thrown")
                AND_THEN ("No errors are returned")
                AND_THEN ("Answer is valid")
                AND_THEN ("The answer makes sense")
            {
                REQUIRE_FALSE(exception);

                REQUIRE(ret.error_code == 0);
                REQUIRE(ret.http_error_code == 200);

                REQUIRE(emoji.valid());

                REQUIRE(emoji.url() != "");
            }
        }
    }
}

