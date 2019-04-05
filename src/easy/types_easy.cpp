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

#include "types_easy.hpp"

using namespace Mastodon;

Easy::time::operator const system_clock::time_point()
{
    return timepoint;
}

Easy::time::operator const string()
{
    return strtime("%FT%T%z", true);
}

const string Easy::time::strtime(const string &format, const bool &local) const
{
    constexpr std::uint16_t bufsize = 1024;
    std::time_t time = system_clock::to_time_t(timepoint);
    std::tm *timeinfo;
    if (local)
    {
        timeinfo = std::localtime(&time);
    }
    else
    {
        timeinfo = std::gmtime(&time);
    }

    char buffer[bufsize];
    std::strftime(buffer, bufsize, format.c_str(), timeinfo);

    return static_cast<const string>(buffer);
}

std::ostream &Mastodon::Easy::operator <<(std::ostream &out,
                                          const Easy::time &t)
{
    out << t.strtime("%FT%T%z", true);
    return out;
}