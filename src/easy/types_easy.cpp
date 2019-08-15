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

#include "types_easy.hpp"

namespace Mastodon
{
namespace Easy
{
    time_type::operator const system_clock::time_point() const
    {
        return timepoint;
    }

    time_type::operator const string() const
    {
        return strtime("%FT%T%z", true);
    }

    const string time_type::strtime(const string &format, const bool &local) const
    {
        constexpr std::uint16_t bufsize = 1024;
        std::time_t time = system_clock::to_time_t(timepoint);
        std::tm *tm;
        if (local)
        {
            tm = std::localtime(&time);
        }
        else
        {
            tm = std::gmtime(&time);
        }

        char buffer[bufsize];
        std::strftime(buffer, bufsize, format.c_str(), tm);

        return static_cast<const string>(buffer);
    }

    std::ostream &operator <<(std::ostream &out,
                              const time_type &t)
    {
        const string s = t;         // Converts using operator const string().
        out << s;
        return out;
    }
}
}
