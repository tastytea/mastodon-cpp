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

#include "return_types.hpp"

namespace Mastodon
{
    return_base::operator bool()
    {
        if (error_code == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return_base::operator uint8_t()
    {
        return error_code;
    }

    return_call::operator const string() const
    {
        return answer;
    }

    std::ostream &operator <<(std::ostream &out, const return_call &ret)
    {
        out << ret.answer;
        return out;
    }

    return_call::return_call()
    {}

    return_call::return_call(const uint8_t ec, const string &em,
                             const uint16_t hec, const string &a)
        : answer(a)
    {
        error_code = ec;
        error_message = em;
        http_error_code = hec;
    }
}
