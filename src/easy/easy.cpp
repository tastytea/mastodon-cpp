/*  This file is part of mastodon-cpp.
 *  Copyright © 2018 tastytea <tastytea@tastytea.de>
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

#include <ctime>
#include <iomanip>  // get_time
#include <sstream>
#include <regex>
#include "easy.hpp"
#include "macros.hpp"

using namespace Mastodon;
using std::string;

Easy::Easy(const string &instance, const string &access_token)
: API(instance, access_token)
{}

const std::vector<string> Easy::json_array_to_vector(const string &json)
{
    Json::Value json_array;
    std::stringstream ss(json);
    ss >> json_array;

    if (json_array.isArray())
    {
        std::vector<string> vec;
        for (const Json::Value &value : json_array)
        {
            vec.push_back(value.toStyledString());
        }
        return vec;
    }

    ttdebug << "ERROR: JSON string holds no array\n";
    ttdebug << "String was: " << json << '\n';
    return {};
}

const std::vector<Easy::stream_event>
    Easy::parse_stream(const std::string &streamdata)
{
    string stream = streamdata;
    std::regex reevent("event: (update|notification|delete)\ndata: (.*)\n");
    std::smatch match;
    std::vector<stream_event> vec = {};

    while (std::regex_search(stream, match, reevent))
    {
        const string &event = match[1].str();
        const string &data = match[2].str();
        event_type type = event_type::Undefined;

        if (event.compare("update") == 0)
            type = event_type::Update;
        else if (event.compare("notification") == 0)
            type = event_type::Notification;
        else if (event.compare("delete") == 0)
            type = event_type::Delete;

        vec.push_back(stream_event(type, data));
        stream = match.suffix().str();
    }

    return vec;
}

const Easy::Link Easy::get_link() const
{
    return Link(get_header("Link"));
}

const string Easy::strtime_utc(const system_clock::time_point &timepoint,
                               const string &format)
{
    return strtime(timepoint, format, true);
}

const string Easy::strtime_local(const system_clock::time_point &timepoint,
                                 const string &format)
{
    return strtime(timepoint, format, false);
}

const string Easy::strtime(const system_clock::time_point &timepoint,
                           const string &format, const bool &utc)
{
    constexpr std::uint16_t bufsize = 1024;
    std::time_t time = system_clock::to_time_t(timepoint);
    std::tm *timeinfo;
    if (utc)
    {
        timeinfo = std::gmtime(&time);
    }
    else
    {
        timeinfo = std::localtime(&time);
    }
    char buffer[bufsize];

    std::strftime(buffer, bufsize, format.c_str(), timeinfo);

    return buffer;
}

Easy::Link::Link(const string &link_header)
: _next()
, _prev()
{
    std::regex renext("max_id=([[:digit:]]*)");
    std::regex reprev("since_id=([[:digit:]]*)");
    std::smatch match;

    if (std::regex_search(link_header, match, renext))
    {
        _next = match[1].str();
    }
    if (std::regex_search(link_header, match, reprev))
    {
        _prev = match[1].str();
    }
}

const string Easy::Link::next() const
{
    return _next;
}

const string Easy::Link::max_id() const
{
    return _next;
}

const string Easy::Link::prev() const
{
    return _prev;
}

const string Easy::Link::since_id() const
{
    return _prev;
}
