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
    /*!
     *  @brief  A list of all API calls.
     *
     *          The original `/` are substituted by `_`. Currently only GET
     *          requests.
     */
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

    /*!
     *  @brief  Constructs a new API object.
     *
     *  @param  instance      The hostname of your instance
     *  @param  access_token  Your access token. You have to generate it
     *                        manually for now.
     */
    explicit API(const std::string &instance,
                 const std::string &access_token);

    /*!
     *  @brief  Make a GET request which doesn't require an argument.
     *
     *  @param  call    A call defined in Mastodon::API::v1
     *
     *  @return The answer from the server. Usually JSON.
     */
    const std::string get(const Mastodon::API::v1 &call);

    /*!
     *  @brief  Make a GET request which requires an argument
     *
     *  @param  call      A call defined in Mastodon::API::v1
     *  @param  argument  The non-optional argument
     *
     *  @return The answer from the server. Usually JSON.
     */
    const std::string get(const Mastodon::API::v1 &call,
                          const std::string &argument);

    /*!
     *  @brief  Make a GET request which doesn't require an argument, pass
     *          optional parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A std::vector containing optional parameters in the
     *                      form `field=value`
     *
     *  @return The answer from the server. Usually JSON.
     */
    const std::string get(const Mastodon::API::v1 &call,
                          const std::vector<std::string> &parameters);

    /*!
     *  @brief  Make a GET request which requires an argument, pass optional
     *          parameters.
     *
     *          Example:
     *
     *              Mastodon::API masto(argv[1], argv[2]);
     *             std::vector<std::string> parameters =
     *             {
     *                 "limit=2",
     *                 "only_media=1"
     *             };
     *             masto.get(Mastodon::API::v1::accounts_id_statuses, "12345", parameters);
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  argument    The non-optional argument
     *  @param  parameters  A std::vector containing optional parameters in the
     *                      form `field=value`
     *
     *  @return The answer from the server. Usually JSON.
     */
    const std::string get(const Mastodon::API::v1 &call,
                          const std::string &argument,
                          const std::vector<std::string> &parameters);

    /*!
     *  @brief  Make a custom GET request.
     *
     *  @param  call    String in the form `/api/v1/example`
     *
     *  @return The answer from the server. Usually JSON.
     */
    const std::string get(const std::string &call);

    /*!
     *  @brief  Sets the useragent. Default is mastodon-cpp/version.
     *
     *  @param  useragent  The useragent
     */
    const void set_useragent(const std::string &useragent);

    /*!
     *  @brief  Gets the useragent.
     *
     *  @return The useragent.
     */
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
