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
#include "easy/entities/attachment.hpp"
#include "../environment_variables.hpp"

using namespace Mastodon;

// We use a media attachment that is attached to a status, therefore we get an
// error.
SCENARIO ("/api/v1/media/:id can be called successfully",
          "[api][auth][mastodon][pleroma][glitch-soc]")
{
    REQUIRE (access_token != nullptr);

    GIVEN ("instance = " + instance + ", media ID = " + media_id)
    {
        Mastodon::Easy::API masto(instance, access_token);
        return_call ret;
        Easy::Attachment attachment;
        bool exception = false;

        WHEN ("PUT /api/v1/media/" + media_id + " is called")
        {
            try
            {
                ret = masto.put(API::v1::media_id,
                                {
                                    { "id", { media_id }},
                                    { "description", { "Test description." }}
                                });
                attachment.from_string(ret.answer);
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
                REQUIRE(ret.http_error_code == 500);
            }
        }
    }
}

