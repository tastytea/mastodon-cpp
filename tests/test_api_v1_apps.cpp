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
#include "easy/entities/application.hpp"
#include "environment_variables.hpp"

using namespace Mastodon;

SCENARIO ("/api/v1/apps can be called successfully",
          "[api][mastodon][pleroma][glitch-soc]")
{
    GIVEN ("instance = " + instance)
    {
        Mastodon::Easy::API masto(instance, "");
        return_call ret;
        Easy::Application app;
        bool exception = false;

        WHEN ("/api/v1/apps is called")
        {
            try
            {
                ret = masto.post
                    (API::v1::apps,
                     {
                         { "client_name", { "mastodon-cpp test" } },
                         { "redirect_uris", { "urn:ietf:wg:oauth:2.0:oob" } },
                         { "scopes", { "read:favourites" } },
                     });
                app.from_string(ret.answer);
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

                REQUIRE(app.valid());

                REQUIRE(app.name() == "mastodon-cpp test");
            }
        }
    }
}
