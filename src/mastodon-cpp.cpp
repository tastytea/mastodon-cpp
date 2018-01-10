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

#include <string>
#include "version.hpp"
#include "mastodon-cpp.hpp"

using namespace Mastodon;
using std::string;

API::API(const string &instance, const string &access_token)
: _instance(instance)
, _access_token(access_token)
, _useragent(string("mastodon-cpp/") + global::version)
, _http(*this, instance, access_token)
{
    //
}

const void API::set_useragent(const std::string &useragent)
{
    _useragent = useragent;
}

const std::string API::get_useragent() const
{
    return _useragent;
}
