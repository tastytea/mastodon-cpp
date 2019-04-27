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
#include "easy/entities/list.hpp"
#include "environment_variables.hpp"

using namespace Mastodon;

SCENARIO ("/api/v1/lists/:id can be called successfully",
          "[api][auth][mastodon][pleroma][glitch-soc]")
{
    REQUIRE (access_token != nullptr);

    GIVEN ("instance = " + instance + ", list ID = " + list_id)
    {
        Mastodon::Easy::API masto(instance, access_token);
        return_call ret;
        Easy::List list;
        bool exception = false;

        WHEN ("GET /api/v1/lists/" + list_id + " is called")
        {
            try
            {
                ret = masto.get(API::v1::lists_id,
                                {{ "id", { list_id }}});
                list.from_string(ret.answer);
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

                REQUIRE(list.valid());

                REQUIRE(list.id() == list_id);
            }
        }

        WHEN ("PUT /api/v1/lists/" + list_id + " is called")
        {
            try
            {
                ret = masto.put(API::v1::lists_id,
                                {
                                    { "id", { list_id }},
                                    { "title", { "testlist" }}
                                });
                list.from_string(ret.answer);
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

                REQUIRE(list.valid());

                REQUIRE(list.title() == "testlist");
            }
        }

        WHEN ("DELETE /api/v1/lists/donotdelete is called")
        {
            try
            {
                ret = masto.del(API::v1::lists_id,
                                {{ "id", { "donotdelete" }}});
            }
            catch (const std::exception &e)
            {
                exception = true;
                WARN(e.what());
            }

            THEN("No exception is thrown")
                AND_THEN ("No unexpected errors are returned")
            {
                REQUIRE_FALSE(exception);

                REQUIRE(ret.error_code == 111);
                REQUIRE(ret.http_error_code == 400);
            }
        }
    }
}

