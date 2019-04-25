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

#define CATCH_CONFIG_MAIN

#include <cstdlib>
#include <catch.hpp>
#include "environment_variables.hpp"

using std::string;
using std::getenv;

// Declared in environment_variables.hpp
const char *env_instance = getenv("MASTODON_CPP_INSTANCE");
const string instance = (env_instance ? env_instance : "likeable.space");
const char *access_token = getenv("MASTODON_CPP_ACCESS_TOKEN");
const char *env_user_id = getenv("MASTODON_CPP_USER_ID");
const string user_id = (env_user_id ? env_user_id : "9hnrrVPriLiLVAhfVo");
const char *env_status_id = getenv("MASTODON_CPP_STATUS_ID");
const string status_id = (env_status_id ? env_status_id : "9hwnuJMq3eTdO4s1PU");
const char *env_filter_id = getenv("MASTODON_CPP_FILTER_ID");
const string filter_id = (env_filter_id ? env_filter_id : "");
const char *env_list_id = getenv("MASTODON_CPP_LIST_ID");
const string list_id = (env_list_id ? env_list_id : "1");
