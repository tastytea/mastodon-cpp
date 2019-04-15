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
#include <catch.hpp>
#include "mastodon-cpp.hpp"
#include "easy/easy.hpp"

SCENARIO ("Instantiating API classes works")
{
    bool exception = false;

    WHEN ("Mastodon::API")
    {
        try
        {
            Mastodon::API masto("social.example.com", "");
        }
        catch (const std::exception &e)
        {
            exception = true;
        }

        THEN ("No exception is thrown")
        {
            REQUIRE_FALSE(exception);
        }
    }

    WHEN ("Mastodon::Easy::API")
    {
        try
        {
            Mastodon::Easy::API masto("social.example.com", "");
        }
        catch (const std::exception &e)
        {
            exception = true;
        }

        THEN ("No exception is thrown")
        {
            REQUIRE_FALSE(exception);
        }
    }
}
