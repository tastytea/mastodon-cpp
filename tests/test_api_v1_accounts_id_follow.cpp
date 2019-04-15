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
#include <cstdlib>
#include <catch.hpp>
#include "mastodon-cpp.hpp"
#include "easy/easy.hpp"
#include "easy/entities/relationship.hpp"

using namespace Mastodon;

SCENARIO ("/api/v1/accounts/:id/follow can be called successfully",
          "[api][mastodon][pleroma][glitch-soc]")
{
    const char *env_instance = std::getenv("MASTODON_CPP_INSTANCE");
    const string instance = (env_instance ? env_instance : "likeable.space");
    const char *access_token = std::getenv("MASTODON_CPP_ACCESS_TOKEN");
    const char *env_user_id = std::getenv("MASTODON_CPP_USER_ID");
    const string user_id = (env_user_id ? env_user_id : "9hnrrVPriLiLVAhfVo");

    GIVEN ("instance = " + instance + ", user ID = " + user_id)
    {
        Mastodon::Easy::API masto(instance, access_token);
        return_call ret;
        Easy::Relationship relationship;
        bool exception = false;


        REQUIRE (access_token != nullptr);

        WHEN ("/api/v1/accounts/" + user_id + "/follow is called")
        {
            try
            {
                ret = masto.post(API::v1::accounts_id_follow,
                                 {
                                     { "id", { user_id } },
                                 });
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

                // You can't follow yourself, so we look for errors too.
                REQUIRE((ret.error_code == 0
                         || ret.error_code == 111));
                REQUIRE((ret.http_error_code == 200
                         || ret.http_error_code == 500));

                REQUIRE((relationship.following()
                         || relationship.error() != ""));
            }
        }
    }
}
