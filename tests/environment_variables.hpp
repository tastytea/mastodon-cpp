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

#ifndef MASTODON_CPP_TEST_ENVIRONMENT_VARIABLES_HPP
#define MASTODON_CPP_TEST_ENVIRONMENT_VARIABLES_HPP

#include <string>

using std::string;

// Defined in main.cpp
extern const char *env_instance;
extern const string instance;
extern const char *access_token;
extern const char *env_user_id;
extern const string user_id;
extern const char *env_status_id;
extern const string status_id;
extern const char *env_filter_id;
extern const string filter_id;
extern const char *env_list_id;
extern const string list_id;

#endif  // MASTODON_CPP_TEST_ENVIRONMENT_VARIABLES_HPP
