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
#include <map>
#include <memory>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>

/*!
 *  @example example01_dump_json.cpp
 *  @example example02_parse_account.cpp
 *  @example example03_mastocron.cpp
 *  @example example04_update_credentials.cpp
 *  @example example05_follow_unfollow.cpp
 *  @example example06_toot_delete-toot.cpp
 *  @example example07_register_app.cpp
 *  @example example08_rate_limiting.cpp
 *  @example example09_streaming_api.cpp
 *  @example example10_simplify.cpp
 */
namespace Mastodon
{
/*!
 *  @brief  Class for the Mastodon API. All input is expected to be UTF-8.
 *          Binary data must be base64-encoded or a filename.
 *  @section error Error codes
 *  mastodon-cpp will never use error codes below 11, except 0.
 *  |      Code | Explanation                   |
 *  | --------: |:------------------------------|
 *  |         0 | No error                      |
 *  |        11 | Invalid call                  |
 *  |        12 | Not implemented               |
 *  |        13 | URL changed (HTTP 301 or 308) |
 *  |        14 | Aborted by user               |
 *  |        20 | Failed to connect             |
 *  |        21 | Couldn't resolve host         |
 *  |        22 | Network is unreachable        |
 *  | 100 - 999 | HTTP status codes             |
 *  |     65535 | Unknown exception             |
 */
class API
{
public:
    /*!
     *  @brief  http class. Do not use this directly.
     */
    class http
    {
    public:
        enum class method
        {
            GET,
            PATCH,
            POST,
            PUT,
            DELETE,
            GET_STREAM
        };

        explicit http(const API &api, const std::string &instance,
                      const std::string &access_token);
        ~http();
        const std::uint16_t request_sync(const method &meth,
                                         const std::string &path,
                                         std::string &answer);

        /*!
         *  @brief  Blocking request.
         *  
         *  
         *
         *  @param  meth      The method defined in http::method
         *  @param  path      The api call as string
         *  @param  formdata  The form data for PATCH and POST request.
         *  @param  answer    The answer from the server
         *
         *  @return @ref error "Error code". If the URL has permanently changed,
         *  13 is returned and answer is set to the new URL.
         */
        const std::uint16_t request_sync(const method &meth,
                                         const std::string &path,
                                         const curlpp::Forms &formdata,
                                         std::string &answer);

        const void get_headers(std::string &headers) const;

        const size_t callback(char* data, size_t size, size_t nmemb,
                              std::string *oss);

        /*!
         *  @brief  Aborts the stream. Use only with streams.
         *  
         *          Aborts the stream next time data comes in. Can take a few
         *          seconds.
         *          This works only with streams, because only streams have an
         *          own http object.
         */ 
        const void abort_stream();

    private:
        const API &parent;
        const std::string _instance;
        const std::string _access_token;
        std::string _headers;
        bool _abort_stream;
    };

    /*!
     *  @brief Used for passing (most of the time) optional parameters.
     *  
     *  Example:
     *  @code
     *  parametermap p =
     *  {
     *      {"field1", { "value1", "value2" } },
     *      {"field2", { "value" } }
     *  }
     *  @endcode
     */
    typedef std::map<std::string, std::vector<std::string>> parametermap;
    /*!
     *  @brief  A list of all API calls.
     *
     *          The original `/` are substituted by `_`.
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
        timelines_list_list_id,
        // PATCH
        accounts_update_credentials,
        // POST
        accounts_id_follow,
        accounts_id_unfollow,
        accounts_id_block,
        accounts_id_unblock,
        accounts_id_mute,
        accounts_id_unmute,
        apps,
        follow_requests_id_authorize,
        follow_requests_id_reject,
        follows,
        media,
        notifications_clear,
        notifications_dismiss,
        statuses,
        statuses_id_reblog,
        statuses_id_unreblog,
        statuses_id_favourite,
        statuses_id_unfavourite,
        statuses_id_pin,
        statuses_id_unpin,
        statuses_id_mute,
        statuses_id_unmute,
        // Streaming
        streaming_user,
        streaming_public,
        streaming_public_local,
        streaming_hashtag,
        streaming_list
    };

    /*!
     *  @brief  Constructs a new API object.
     *
     *          To register your application, leave access_token blank and call
     *          register_app1() and register_app2().
     *
     *  @param  instance      The hostname of your instance
     *  @param  access_token  Your access token.
     */
    explicit API(const std::string &instance,
                 const std::string &access_token);

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

    /*!
     *  @brief  Returns the instance.
     *
     *  @return The instance.
     */
    const std::string get_instance() const;

    /*!
     *  @brief  Percent-encodes a string. This is done automatically, unless you
     *          make a custom request.
     *          
     *          Calls curlpp::escape(str)
     *
     *          The only time you should use this, is if you use
     *          get(const std::string &call, std::string &answer).
     *          
     *          See RFC 3986 section 2.1 for more info.
     *
     *  @param  str     The string
     *
     *  @return The percent-encoded string
     */
    const std::string urlencode(const std::string &str) const;

    /*!
     *  @brief  Register application, step 1/2
     *
     *  @param  client_name    The name of the application
     *  @param  redirect_uri   urn:ietf:wg:oauth:2.0:oob for none
     *  @param  scopes         Scopes (read, write, follow, space separated)
     *  @param  website        The website of the application
     *  @param  client_id      Returned
     *  @param  client_secret  Returned
     *  @param  url            Returned, used to generate code for register_app2
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and url is set to the new URL.
     */
    const std::uint16_t register_app1(const std::string &client_name,
                                      const std::string &redirect_uri,
                                      const std::string &scopes,
                                      const std::string &website,
                                      std::string &client_id,
                                      std::string &client_secret,
                                      std::string &url);

    /*!
     *  @deprecated Will vanish in 1.0.0
     */
    const std::uint16_t register_app1(const std::string &instance,
                                      const std::string &client_name,
                                      const std::string &redirect_uri,
                                      const std::string &scopes,
                                      const std::string &website,
                                      std::string &client_id,
                                      std::string &client_secret,
                                      std::string &url);

    /*!
     *  @brief  Register application, step 2/2
     *  
     *          The access token will be used in all subsequent calls.
     *
     *  @param  client_id      
     *  @param  client_secret  
     *  @param  redirect_uri   urn:ietf:wg:oauth:2.0:oob for none
     *  @param  code           The code generated by the website
     *  @param  access_token   Returned
     *
     *  @return @ref error "Error code".
     */
    const std::uint16_t register_app2(const std::string &client_id,
                                      const std::string &client_secret,
                                      const std::string &redirect_uri,
                                      const std::string &code,
                                      std::string &access_token);

    /*!
     *  @deprecated Will vanish in 1.0.0
     */
    const std::uint16_t register_app2(const std::string &instance,
                                      const std::string &client_id,
                                      const std::string &client_secret,
                                      const std::string &redirect_uri,
                                      const std::string &code,
                                      std::string &access_token);

    /*!
     *  @brief  Make a GET request which doesn't require an argument.
     *
     *  @param  call    A call defined in Mastodon::API::v1
     *  @param  answer  The answer from the server. Usually JSON. On error an
     *                  empty string.
     *
     *  @return @ref error "Error code".
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
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t get(const Mastodon::API::v1 &call,
                            const std::string &argument,
                            std::string &answer);

    /*!
     *  @brief  Make a GET request which doesn't require an argument, pass
     *          parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t get(const Mastodon::API::v1 &call,
                            const parametermap &parameters,
                            std::string &answer);

    /*!
     *  @brief  Make a GET request which requires an argument, pass parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  argument    The non-optional argument
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t get(const Mastodon::API::v1 &call,
                            const std::string &argument,
                            const parametermap &parameters,
                            std::string &answer);

    /*!
     *  @brief  Make a custom GET request.
     *
     *  @param  call    String in the form `/api/v1/example`
     *  @param  answer  The answer from the server. Usually JSON. On error an
     *                  empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t get(const std::string &call,
                            std::string &answer);

    /*!
     *  @brief  Make a streaming GET request.
     *
     *  @param  call      A call defined in Mastodon::API::v1
     *  @param  argument  The non-optional argument
     *  @param  answer    The answer from the server. Events with JSON-payload.
     *  @param  ptr       Pointer to the http object. Can be used to call
     *                    ptr->abort_stream()
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t get_stream(const Mastodon::API::v1 &call,
                                   const std::string &argument,
                                   std::string &answer,
                                   std::unique_ptr<Mastodon::API::http> &ptr);

    /*!
     *  @brief  Make a streaming GET request.
     *
     *  @param  call      A call defined in Mastodon::API::v1
     *  @param  answer    The answer from the server. Events with JSON-payload.
     *  @param  ptr       Pointer to the http object. Can be used to call
     *                    ptr->abort_stream()
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t get_stream(const Mastodon::API::v1 &call,
                                   std::string &answer,
                                   std::unique_ptr<Mastodon::API::http> &ptr);

    /*!
     *  @brief  Make a streaming GET request.
     *
     *  @param  call      String in the form `/api/v1/example`
     *  @param  answer    The answer from the server. Usually JSON. On error an
     *                    empty string.
     *  @param  ptr       Pointer to the http object. Can be used to call
     *                    ptr->abort_stream()
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t get_stream(const std::string &call,
                                   std::string &answer,
                                   std::unique_ptr<Mastodon::API::http> &ptr);

    /*!
     *  @brief  Make a PATCH request.
     *
     *          Binary data must be base64-encoded or a filename.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t patch(const Mastodon::API::v1 &call,
                              const parametermap &parameters,
                              std::string &answer);

    /*!
     *  @brief  Make a POST request which doesn't require an argument.
     *
     *  @param  call    A call defined in Mastodon::API::v1
     *  @param  answer  The answer from the server. Usually JSON. On error an
     *                  empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t post(const Mastodon::API::v1 &call,
                             std::string &answer);

    /*!
     *  @brief  Make a POST request which requires an argument
     *
     *  @param  call      A call defined in Mastodon::API::v1
     *  @param  argument  The non-optional argument
     *  @param  answer    The answer from the server. Usually JSON. On error an
     *                    empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t post(const Mastodon::API::v1 &call,
                             const std::string &argument,
                             std::string &answer);

    /*!
     *  @brief  Make a POST request which doesn't require an argument, pass
     *          parameters.
     *
     *          Binary data must be base64-encoded or a filename.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t post(const Mastodon::API::v1 &call,
                             const parametermap &parameters,
                             std::string &answer);

    /*!
     *  @brief  Make a POST request which requires an argument, pass parameters.
     *
     *          Binary data must be base64-encoded or a filename.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  argument    The non-optional argument
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t post(const Mastodon::API::v1 &call,
                             const std::string &argument,
                             const parametermap &parameters,
                             std::string &answer);

    /*!
     *  @brief  Make a custom POST request.
     *
     *          Binary data must be base64-encoded or a filename.
     *
     *  @param  call        String in the form `/api/v1/example`
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t post(const std::string &call,
                             const parametermap &parameters,
                             std::string &answer);

    /*!
     *  @brief  Make a PUT request which requires an argument, pass parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  argument    The non-optional argument
     *  @param  parameters  A Mastodon::API::parametermap containing
     *                      parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t put(const Mastodon::API::v1 &call,
                            const std::string &argument,
                            const parametermap &parameters,
                            std::string &answer);

    /*!
     *  @brief  Make a custom PUT request.
     *
     *  @param  call        String in the form `/api/v1/example`
     *  @param  parameters  A Mastodon::API::parametermap containing
     *                      parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t put(const std::string &call,
                            const parametermap &parameters,
                            std::string &answer);

    /*!
     *  @brief  Make a DELETE request which requires an argument
     *
     *  @param  call      A call defined in Mastodon::API::v1
     *  @param  argument  The non-optional argument
     *
     *  @return @ref error "Error code".
     */
    const std::uint16_t del(const Mastodon::API::v1 &call,
                            const std::string &argument);

    /*!
     *  @brief  Make a DELETE request which doesn't require an argument, pass
     *          parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *
     *  @return @ref error "Error code".
     */
    const std::uint16_t del(const Mastodon::API::v1 &call,
                            const parametermap &parameters);

    /*!
     *  @brief  Make a DELETE request which requires an argument, pass
     *          parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  argument    The non-optional argument
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *
     *  @return @ref error "Error code".
     */
    const std::uint16_t del(const Mastodon::API::v1 &call,
                            const std::string &argument,
                            const parametermap &parameters);

    /*!
     *  @brief  Make a custom DELETE request.
     *
     *  @param  call        String in the form `/api/v1/example`
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    const std::uint16_t del(const std::string &call,
                            const parametermap &parameters,
                            std::string &answer);

    /*!
         *  @brief  Gets the header from the last answer.
         *
         *  @param  header  The header to search
         *
         *  @return The header, or "" on error.
         */
        const std::string get_header(const std::string &header) const;

private:
    const std::string _instance;
    std::string _access_token;
    std::string _useragent;
    http _http;

    /*!
     *  @brief  Converts map of parameters into a string.
     *
     *  @param  map         Map of parameters
     *  @param  firstparam  Contains this map the first parameter?
     *
     *  @return String of parameters
     */
    const std::string maptostr(const parametermap &map,
                               const bool &firstparam = true);

    /*!
     *  @brief  Converts map of parameters into form data
     *
     *  @param  map     Map of parameters
     *
     *  @return Form data as curlpp::Forms
     */
    const curlpp::Forms maptoformdata(const parametermap &map);
};
}

#endif
