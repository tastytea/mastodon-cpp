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

#include "token.hpp"

using namespace Mastodon;
using Token = Easy::Token;

bool Token::valid() const
{
    return Entity::check_valid(
        {
            "access_token",
            "token_type",
            "scope",
            "created_at"
        });
}

const string Token::access_token() const
{
    return get_string("access_token");
}

const string Token::token_type() const
{
    return get_string("token_type");
}

const string Token::scope() const
{
    return get_string("scope");
}

const Easy::time_type Token::created_at() const
{
    return get_time("created_at");
}
