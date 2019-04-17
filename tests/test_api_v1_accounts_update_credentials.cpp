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
#include "easy/entities/account.hpp"
#include "environment_variables.hpp"

using namespace Mastodon;

SCENARIO ("/api/v1/accounts/update_credentials can be called successfully",
          "[api][mastodon][pleroma][glitch-soc]")
{
    REQUIRE (access_token != nullptr);

    GIVEN ("instance = " + instance + ", user ID = " + user_id)
    {
        Mastodon::Easy::API masto(instance, access_token);
        return_call ret;
        Easy::Account account;
        bool exception = false;

        WHEN ("PATCH /api/v1/accounts/update_credentials is called")
        {
            try
            {
                ret = masto.patch(API::v1::accounts_update_credentials,
                                  {{ "display_name", { "testaccount" } }});
                account = Easy::Account(ret.answer);
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

                REQUIRE(account.valid());

                REQUIRE(account.display_name() == "testaccount");
            }
        }
    }
}
