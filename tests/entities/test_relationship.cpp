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
#include <chrono>
#include <catch.hpp>
#include "easy/entities/relationship.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Relationship works as intended", "[entity]")
{
    GIVEN ("An Easy::Relationship object")
    {
        Easy::Relationship relationship;
        bool exception = false;

        WHEN ("It is initialized with valid relationship data")
        {
            const string data =
                "[{\"blocking\" : false,"
                "\"showing_reblogs\" : true,"
                "\"requested\" : false,"
                "\"followed_by\" : false,"
                "\"muting\" : true,"
                "\"domain_blocking\" : false,"
                "\"endorsed\" : false,"
                "\"following\" : true,"
                "\"subscribing\" : false,"
                "\"id\" : \"9jqdKpZIs5D8SOe3e4\","
                "\"muting_notifications\" : false}]";

            try
            {
                relationship.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Relationship is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                REQUIRE(relationship.valid());
                REQUIRE(relationship.id() == "9jqdKpZIs5D8SOe3e4");
                REQUIRE(relationship.blocking() == false);
                REQUIRE(relationship.showing_reblogs() == true);
                REQUIRE(relationship.requested() == false);
                REQUIRE(relationship.followed_by() == false);
                REQUIRE(relationship.muting() == true);
                REQUIRE(relationship.domain_blocking() == false);
                REQUIRE(relationship.endorsed() == false);
                REQUIRE(relationship.following() == true);
                REQUIRE(relationship.muting_notifications() == false);
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                relationship.from_string("");
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("It is not valid")
                AND_THEN ("id is empty")
            {
                REQUIRE_FALSE(exception);
                REQUIRE_FALSE(relationship.valid());
                REQUIRE(relationship.id() == "");
            }
        }
    }
}
