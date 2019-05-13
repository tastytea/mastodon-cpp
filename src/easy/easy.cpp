/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
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
#include <algorithm>
#include "easy.hpp"
#include "debug.hpp"

using namespace Mastodon;

Easy::API::API(const string &instance, const string &access_token)
    : Mastodon::API(instance, access_token)
{}

const std::vector<string> Easy::json_array_to_vector(const string &json)
{
    Json::Value json_array;
    std::stringstream ss(json);
    ss >> json_array;

    if (json_array.isArray())
    {
        // Transform array of Json::Value to vector of string.
        std::vector<string> vec(json_array.size());
        std::transform(json_array.begin(), json_array.end(), vec.begin(),
                       [](const Json::Value &j)
                           { return j.toStyledString(); });
        return vec;
    }

    ttdebug << "ERROR: JSON string holds no array\n";
    ttdebug << "String was: " << json << '\n';
    return {};
}

const vector<Easy::stream_event_type> Easy::parse_stream(
    const std::string &streamdata)
{
    string stream = streamdata;
    std::regex reevent("event: (update|notification|delete|ERROR)\ndata: (.*)\n");
    std::smatch match;
    std::vector<stream_event_type> vec = {};

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
        else if (event.compare("ERROR") == 0)
            type = event_type::Error;

        vec.push_back({ type, data });
        stream = match.suffix().str();
    }

    return vec;
}

const Easy::time_type Easy::string_to_time(const string &strtime)
{
    std::stringstream sstime(strtime);
    struct std::tm tm = {};
    tm.tm_isdst = -1;       // Detect daylight saving time.
    sstime >> std::get_time(&tm, "%Y-%m-%dT%T");
    std::time_t time = timegm(&tm); // Assume time is UTC.
    return { system_clock::from_time_t(time) };
}

const Easy::Link Easy::API::get_link() const
{
    return Link(get_header("Link"));
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
