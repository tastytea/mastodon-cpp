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
#include "easy/entities/account.hpp"

using namespace Mastodon;

SCENARIO ("/api/v1/accounts/verify_credentials can be called successfully",
          "[api][mastodon][pleroma][glitch-soc]")
{
    GIVEN ("access token and return_call")
    {
        const char *access_token = std::getenv("MASTODON_CPP_ACCESS_TOKEN");
        return_call ret;
        bool exception = false;
        bool username_found = false;

        REQUIRE (access_token != nullptr);

        GIVEN ("Mastodon::API")
        {
            Mastodon::API masto("likeable.space", access_token);

            WHEN ("/api/v1/accounts/verify_credentials is called")
            {
                try
                {
                    ret = masto.get(API::v1::accounts_verify_credentials);
                    username_found = ret.answer.find(
                        "\"username\":\"testaccount\"") != std::string::npos;
                }
                catch (const std::exception &e)
                {
                    exception = true;
                }
                THEN("No exception is thrown")
                {
                    REQUIRE_FALSE(exception);
                }
                THEN ("No errors are returned")
                {
                    REQUIRE(ret.error_code == 0);
                    REQUIRE(ret.http_error_code == 200);
                }
                THEN ("The answer makes sense")
                {
                    REQUIRE(username_found);
                }
            }
        }

        GIVEN ("Mastodon::Easy::API")
        {
            Mastodon::Easy::API masto("likeable.space", access_token);
            Easy::Account account;

            WHEN ("/api/v1/accounts/verify_credentials is called")
            {
                try
                {
                    ret = masto.get(API::v1::accounts_verify_credentials);
                    account = Easy::Account(ret.answer);
                }
                catch (const std::exception &e)
                {
                    exception = true;
                }
                THEN("No exception is thrown")
                {
                    REQUIRE_FALSE(exception);
                }
                THEN ("No errors are returned")
                {
                    REQUIRE(ret.error_code == 0);
                    REQUIRE(ret.http_error_code == 200);
                }
                THEN ("Answer is valid")
                {
                    REQUIRE(account.valid());
                }
                THEN ("The answer makes sense")
                {
                    REQUIRE(account.username() == "testaccount");
                }
            }
        }
    }
}
