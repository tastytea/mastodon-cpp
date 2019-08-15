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
#include "easy/entities/filter.hpp"
#include "easy/easy.hpp"

using std::string;
using std::chrono::system_clock;

using namespace Mastodon;

SCENARIO ("Easy::Filter works as intended", "[entity]")
{
    GIVEN ("An Easy::Filter object")
    {
        Easy::Filter filter;
        bool exception = false;

        WHEN ("It is initialized with valid filter data")
        {
            const string data =
                "{\"whole_word\":false,"
                "\"phrase\":\"nöööö!\","
                "\"irreversible\":null,"
                "\"id\":\"2\","
                "\"expires_at\":null,"
                "\"context\":[\"public\",\"notifications\"]}";

            try
            {
                filter.from_string(data);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("Filter is valid")
                AND_THEN ("The attributes are set to the right values")
            {
                REQUIRE_FALSE(exception);
                // REQUIRE(filter.valid()); // Pleroma issue #885.
                REQUIRE(!filter.whole_word());
                REQUIRE(filter.phrase() == "nöööö!");
                REQUIRE(!filter.irreversible());
                REQUIRE(filter.id() == "2");
                REQUIRE(filter.expires_at().timepoint
                        == system_clock::time_point());
                REQUIRE(filter.context() == std::vector<Easy::context_type>
                        ({
                            Easy::context_type::Public,
                            Easy::context_type::Notifications
                        }));
            }
        }

        WHEN ("It is initialized with an empty string")
        {
            try
            {
                filter.from_string("");
            }
            catch (const std::exception &e)
            {
                exception = true;
            }

            THEN ("No exception is thrown")
                AND_THEN ("It is not valid")
                AND_THEN ("phrase is empty")
            {
                REQUIRE_FALSE(exception);
                REQUIRE_FALSE(filter.valid());
                REQUIRE(filter.phrase() == "");
            }
        }
    }
}
