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

using namespace Mastodon;

SCENARIO ("/api/v1/accounts/:id can be called successfully",
          "[api][mastodon][pleroma][glitch-soc]")
{
    GIVEN ("Mastodon::API")
    {
        Mastodon::API masto("likeable.space", "");
        return_call ret;
        bool exception = false;
        bool username_found = false;

        WHEN ("/api/v1/accounts/9hnrrVPriLiLVAhfVo is called")
        {
            try
            {
                ret = masto.get(API::v1::accounts_id,
                                {{ "id", { "9hnrrVPriLiLVAhfVo" }}});
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
        Mastodon::Easy::API masto("likeable.space", "");
        return_call ret;
        Easy::Account account;
        bool exception = false;

        WHEN ("/api/v1/accounts/9hnrrVPriLiLVAhfVo is called")
        {
            try
            {
                ret = masto.get(API::v1::accounts_id,
                                {{ "id", { "9hnrrVPriLiLVAhfVo" }}});
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
