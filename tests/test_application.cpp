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
#include "easy/entities/application.hpp"

using std::string;

SCENARIO ("Easy::Application works as intended", "[entity]")
{
    GIVEN ("An Easy::Application object")
    {
        Mastodon::Easy::Application app;
        bool exception = false;

        WHEN ("It is initialized with valid application data")
        {
            const string data = "{\"name\" : \"Web\", \"website\" : null}";

            try
            {
                app.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Application is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(app.valid());

                REQUIRE(app.name() == "Web");
                REQUIRE(app.website() == "");
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                app.from_string("");
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("It is not valid")
                AND_THEN ("name is empty")
            {
                REQUIRE_FALSE(exception);
                REQUIRE_FALSE(app.valid());
                REQUIRE(app.name() == "");
            }
        }
    }
}
