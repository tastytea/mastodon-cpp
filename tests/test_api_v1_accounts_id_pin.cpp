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
#include "mastodon-cpp.hpp"
#include "easy/easy.hpp"
#include "easy/entities/relationship.hpp"
#include "environment_variables.hpp"

using namespace Mastodon;

SCENARIO ("/api/v1/accounts/:id/pin can be called successfully",
          "[api][mastodon][glitch-soc]")
{
    REQUIRE (access_token != nullptr);

    GIVEN ("instance = " + instance)
    {
        Mastodon::Easy::API masto(instance, access_token);
        return_call ret;
        bool exception = false;
        Easy::Relationship relationship;

        WHEN ("POST /api/v1/accounts/" + user_id + "/pin is called")
        {
            try
            {
                ret = masto.post(API::v1::accounts_id_pin,
                                 {{ "id", { user_id } }});
                relationship.from_string(ret.answer);
            }
            catch (const std::exception &e)
            {
                exception = true;
                WARN(e.what());
            }

            THEN("No exception is thrown")
                AND_THEN ("No unexpected errors are returned")
                AND_THEN ("The answer makes sense")
            {
                REQUIRE_FALSE(exception);

                // We can't follow our-self, so we look for errors too.
                REQUIRE((ret.error_code == 0
                         || ret.error_code == 111));
                REQUIRE((ret.http_error_code == 200
                         || ret.http_error_code == 422));

                REQUIRE(relationship.id() != "");
            }
        }
    }
}
