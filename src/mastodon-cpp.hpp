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

/*!
 *  @example example1_dump_json.cpp
 *  @example example2_parse_account.cpp
 *  @example example3_mastocron.cpp
 */
namespace Mastodon
{
/*!
 *  @brief  Class for the Mastodon API.
 *  @section error Error codes
 *  |      Code | Explanation                   |
 *  | --------: |:------------------------------|
 *  |         0 | No error                      |
 *  |         1 | Invalid call                  |
 *  |         2 | Not implemented               |
 *  |        16 | Connection failed             |
 *  |        17 | TLS error                     |
 *  |        18 | Invalid response from server  |
 *  | 100 - 999 | HTTP status codes             |
 *  |     65535 | Unknown exception             |
 */
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
     *  @param  answer  The answer from the server. Usually JSON. On error an
     *                  empty string.
     *
     *  @return Error code. See README.md for details.
     */
    const std::uint16_t get(const Mastodon::API::v1 &call, std::string &answer);

    /*!
     *  @brief  Make a GET request which requires an argument
     *
     *  @param  call      A call defined in Mastodon::API::v1
     *  @param  argument  The non-optional argument
     *  @param  answer    The answer from the server. Usually JSON. On error an
     *                    empty string.
     *
     *  @return Error code. See README.md for details.
     */
    const std::uint16_t get(const Mastodon::API::v1 &call,
                            const std::string &argument,
                            std::string &answer);

    /*!
     *  @brief  Make a GET request which doesn't require an argument, pass
     *          optional parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A std::vector containing optional parameters in the
     *                      form `field=value`
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return Error code. See README.md for details.
     */
    const std::uint16_t get(const Mastodon::API::v1 &call,
                            const std::vector<std::string> &parameters,
                            std::string &answer);

    /*!
     *  @brief  Make a GET request which requires an argument, pass optional
     *          parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  argument    The non-optional argument
     *  @param  parameters  A std::vector containing optional parameters in the
     *                      form `field=value`
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return Error code. See README.md for details.
     */
    const std::uint16_t get(const Mastodon::API::v1 &call,
                            const std::string &argument,
                            const std::vector<std::string> &parameters,
                            std::string &answer);

    /*!
     *  @brief  Make a custom GET request.
     *
     *  @param  call    String in the form `/api/v1/example`
     *  @param  answer  The answer from the server. Usually JSON. On error an
     *                  empty string.
     *
     *  @return Error code. See README.md for details.
     */
    const std::uint16_t get(const std::string &call,
                            std::string &answer);

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

        /*!
         *  @brief  Blocking request.
         *
         *  @param  meth    The method defined in http::method
         *  @param  path    The api call as string
         *  @param  data    The form data for PATCH and POST request. Not
         *                  implemented at the moment. This will likely change
         *                  into a std::vector.
         *  @param  answer  The answer from the server
         *
         *  @return Error code. See README.md for details.
         */
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
