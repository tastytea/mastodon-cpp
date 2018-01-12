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

#ifndef MASTODON_CPP_HPP
#define MASTODON_CPP_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace Mastodon
{
    class API
    {
    public:
        enum class v1
        {
            accounts_id,
            accounts_verify_credentials,
            accounts_id_followers,
            accounts_id_following,
            accounts_id_statuses,
            accounts_relationships,
            accounts_search,
            blocks,
            domain_blocks,
            favourites,
            follow_requests,
            instance,
            custom_emojis,
            lists,
            accounts_id_lists,
            lists_id_accounts,
            lists_id,
            mutes,
            notifications,
            notifications_id,
            reports,
            search,
            statuses_id,
            statuses_id_context,
            statuses_id_card,
            statuses_id_reblogged_by,
            statuses_id_favourited_by,
            timelines_home,
            timelines_public,
            timelines_tag_hashtag,
            timelines_list_list_id
        };

        explicit API(const std::string &instance,
                     const std::string &access_token);
        // Select one of the predefined methods.
        const std::string get(const Mastodon::API::v1 &call);
        const std::string get(const Mastodon::API::v1 &call,
                              const std::vector<std::string> &parameters);
        const std::string get(const Mastodon::API::v1 &call,
                              const std::string &argument,
                              const std::vector<std::string> &parameters);
        const std::string get(const Mastodon::API::v1 &call,
                              const std::string &argument);
        // Supply a custom call as string.
        const std::string get(const std::string &call);

        const void set_useragent(const std::string &useragent);
        const std::string get_useragent() const;

    private:
        const std::string _instance;
        const std::string _access_token;
        std::string _useragent;

        class http
        {
        public:
            enum class method
            {
                GET,
                PATCH,
                POST,
                DELETE
            };

            explicit http(const API &api, const std::string &instance,
                          const std::string &access_token);
            const std::uint16_t request_sync(const method &meth,
                                             const std::string &path,
                                             std::string &answer);
            const std::uint16_t request_sync(const method &meth,
                                             const std::string &path,
                                             const std::string &data,
                                             std::string &answer);

        private:
            const API &parent;
            const std::string _instance;
            const std::string _access_token;
            boost::asio::ssl::context _ctx;
            boost::asio::io_service _io_service;
            boost::asio::ip::tcp::resolver _resolver;
            boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _socket;
        } _http;
    };
}

#endif
