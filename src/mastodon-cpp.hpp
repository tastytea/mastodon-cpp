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
#include <array>
#include <mutex>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>

using std::uint_fast16_t;
using std::string;

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
 *  @example example11_post_media.cpp
 *  @example example12_easy_laststatus.cpp
 *  @example example13_easy_stream.cpp
 *  @example example14_easy_treeview.cpp
 *  @example example15_proxy.cpp
 *  @example example16_account_fields.cpp
 */

namespace Mastodon
{
/*!
 *  @brief  Class for the Mastodon API.
 *  
 *          All input is expected to be UTF-8. Binary data must be
 *          base64-encoded or a filename.
 *          It appears that media attachements can not be base64 encoded.
 *  
 *  @section error Error codes
 *  mastodon-cpp will never use error codes below 11, except 0.
 *  |      Code | Explanation                      |
 *  | --------: |:---------------------------------|
 *  |         0 | No error                         |
 *  |        11 | Invalid call                     |
 *  |        12 | Not implemented                  |
 *  |        13 | URL changed (HTTP 301 or 308)    |
 *  |        14 | Cancelled by user                |
 *  |        15 | Network error (curlpp exception) |
 *  |        16 | Timeout                          |
 *  | 100 - 999 | HTTP status codes                |
 *  |     65535 | Unknown error                    |
 *  
 *  @since  before 0.11.0
 */
class API
{
public:
    /*!
     *  @brief  http class. Do not use this directly.
     *  
     *  @since  before 0.11.0
     */
    class http
    {
    public:
        /*!
         *  @brief  HTTP methods
         */
        enum class method
        {
            GET,
            PATCH,
            POST,
            PUT,
            DELETE,
            GET_STREAM
        };

        explicit http(const API &api, const string &instance,
                      const string &access_token);
        ~http();
        uint_fast16_t request(const method &meth,
                                    const string &path,
                                    string &answer);

        /*!
         *  @brief  HTTP Request.
         *
         *  @param  meth      The method defined in http::method
         *  @param  path      The api call as string
         *  @param  formdata  The form data for PATCH and POST requests.
         *  @param  answer    The answer from the server
         *
         *  @return @ref error "Error code". If the URL has permanently changed,
         *  13 is returned and answer is set to the new URL.
         *  
         *  @since  before 0.11.0
         */
        uint_fast16_t request(const method &meth,
                                    const string &path,
                                    const curlpp::Forms &formdata,
                                    string &answer);

        /*!
         *  @brief  Get all headers in a string
         */
        void get_headers(string &headers) const;

        /*!
         *  @brief  Cancels the stream. Use only with streams.
         *  
         *          Cancels the stream next time data comes in. Can take a few
         *          seconds.
         *          This works only with streams, because only streams have an
         *          own http object.
         *          
         *  @since  0.12.2
         */ 
        void cancel_stream();

        /*!
         *  @brief  Gets the mutex guarding the string that is written to.
         *  
         *          The mutex guards the function that writes to the string you
         *          specified in get_stream().
         *
         *  @return A reference of the mutex.
         *  
         *  @since  0.12.3
         */
        std::mutex &get_mutex();

    private:
        const API &parent;
        const string _instance;
        const string _access_token;
        string _headers;
        bool _cancel_stream;
        std::mutex _mutex;

        size_t callback_write(char* data, size_t size, size_t nmemb,
                                    string *oss);
        double callback_progress(double /* dltotal */, double /* dlnow */,
                                 double /* ultotal */, double /* ulnow */);
    };

    /*!
     *  @brief Used for passing parameters.
     *  
     *  Example:
     *  @code
     *  parametermap p =
     *  {
     *      {"field1", { "value1", "value2" } },
     *      {"field2", { "value" } }
     *  }
     *  @endcode
     *  
     *  @since  before 0.11.0
     */
    typedef std::map<string, std::vector<string>> parametermap;

    /*!
     *  @brief  A list of all v1 API calls.
     *  
     *          The original `/` are substituted by `_`.
     *  
     *  @since  before 0.11.0
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
        endorsements,
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
        accounts_id_pin,
        accounts_id_unpin,
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
        // PUT
        media_id,
        // Streaming
        streaming_user,
        streaming_public,
        streaming_public_local,
        streaming_hashtag,
        streaming_list,
        // Push
        push_subscription,
        // Glitch-Soc
        bookmarks,
        statuses_id_bookmark,
        statuses_id_unbookmark
    };

    /*!
     *  @brief  A list of all v2 API calls.
     *  
     *          The original `/` are substituted by `_`.
     *  
     *  @since  0.16.0
     */
    enum class v2
    {
        search
    };

    /*!
     *  @brief  Constructs a new API object.
     *
     *          To register your application, leave access_token blank and call
     *          register_app1() and register_app2().
     *
     *  @param  instance      The hostname of your instance
     *  @param  access_token  Your access token.
     *  
     *  @since  before 0.11.0
     */
    explicit API(const string &instance, const string &access_token);

    /*!
     *  @brief  Sets the useragent. Default is mastodon-cpp/version.
     *
     *  @param  useragent  The useragent
     *  
     *  @since  before 0.11.0
     */
    void set_useragent(const string &useragent);

    /*!
     *  @brief  Gets the useragent.
     *
     *  @return The useragent.
     *  
     *  @since  before 0.11.0
     */
    const string get_useragent() const;

    /*!
     *  @brief  Returns the instance.
     *
     *  @return The instance.
     *  
     *  @since  before 0.11.0
     */
    const string get_instance() const;

    /*!
     *  @brief  Percent-encodes a string. This is done automatically, unless you
     *          make a custom request.
     *          
     *          Calls curlpp::escape(str)
     *
     *          The only time you should use this, is if you use
     *          get(const string &call, string &answer).
     *          
     *          See RFC 3986 section 2.1 for more info.
     *
     *  @param  str     The string
     *
     *  @return The percent-encoded string
     *  
     *  @since  before 0.11.0
     */
    static const string urlencode(const string &str);

    /*!
     *  @brief  Decodes a percent-encoded string.
     *
     *          Calls curlpp::unescape(str)
     *
     *          See RFC 3986 section 2.1 for more info.
     *
     *  @param  str     The string
     *
     *  @return The decoded string
     *
     *  @since  0.18.0
     */
    static const string urldecode(const string &str);

    /*!
     *  @brief  Register application, step 1/2
     *
     *  @param  client_name    The name of the application
     *  @param  redirect_uri   urn:ietf:wg:oauth:2.0:oob for none
     *  @param  scopes         Scopes (`read`, `write`, `follow`, `push`; space
     *                         separated)
     *  @param  website        The website of the application
     *  @param  client_id      Returned
     *  @param  client_secret  Returned
     *  @param  url            Returned, used to generate code for register_app2
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *          is returned and url is set to the new URL.
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t register_app1(const string &client_name,
                                const string &redirect_uri,
                                const string &scopes,
                                const string &website,
                                string &client_id,
                                string &client_secret,
                                string &url);


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
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t register_app2(const string &client_id,
                                const string &client_secret,
                                const string &redirect_uri,
                                const string &code,
                                string &access_token);

    /*!
     *  @brief  Gets the header from the last answer.
     *
     *  @param  header  The header to get
     *
     *  @return The header, or "" on error.
     *  
     *  @since  before 0.11.0
     */
    const string get_header(const string &header) const;

    /*!
     *  @brief  Turn exceptions on or off. Defaults to off.
     *  
     *          This applies to exceptions from curlpp. curlpp::RuntimeError and
     *          curlpp::LogicError.
     *
     *  @param  value   true for on, false for off
     *
     *  @return true if exceptions are turned on, false otherwise
     *  
     *  @since  before 0.11.0
     */
    bool exceptions(const bool &value);

    /*!
     *  @brief  Returns true if exceptions are turned on, false otherwise
     */
    bool exceptions() const;

    /*!
     *  @brief  Replaces HTML entities with UTF-8 characters
     *
     *          Supports named and numbered entities, decimal and hexadecimal.
     *          
     *  @since  0.12.0
     */
    static const string unescape_html(const string &html);

    /*!
     *  @brief  Sets the proxy.
     *
     *          Since mastodon-cpp is built on libcurl, it respects the same
     *          proxy environment variables. See `man curl`.
     *
     *  @param  proxy   See `man 3 CURLOPT_PROXY`
     *  @param  userpw  See `man 3 CURLOPT_PROXYUSERPWD` (optional)
     *
     *  @since  0.15.0
     */
    void set_proxy(const string &proxy, const string &userpw = "");

    /*!
     *  @brief  For internal use
     *
     *  @param  proxy   URL
     *  @param  userpw  username:password
     *
     *  @since  0.15.1
     */
    void get_proxy(string &proxy, string &userpw) const;

    /*!
     *  @brief  Make a GET request which doesn't require parameters.
     *
     *  @param  call    A call defined in Mastodon::API::v1
     *  @param  answer  The answer from the server. Usually JSON. On error an
     *                  empty string.
     *
     *  @return @ref error "Error code".
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t get(const Mastodon::API::v1 &call, string &answer);

    /*!
     *  @brief  Make a GET request which requires parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     */
    uint_fast16_t get(const Mastodon::API::v1 &call,
                      const parametermap &parameters,
                      string &answer);

    /*!
     *  @brief  Make a GET request which requires parameters.
     *
     *  @since  0.16.0
     */
    uint_fast16_t get(const Mastodon::API::v2 &call,
                      const parametermap &parameters,
                      string &answer);

    /*!
     *  @brief  Make a custom GET request.
     *
     *  @param  call    String in the form `/api/v1/example`
     *  @param  answer  The answer from the server. Usually JSON. On error an
     *                  empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t get(const string &call, string &answer);

    /*!
     *  @brief  Make a streaming GET request.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *  @param  answer      The answer from the server. Events with JSON-payload.
     *  @param  ptr         Pointer to the http object. Can be used to call
     *                      ptr->cancel_stream()
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t get_stream(const Mastodon::API::v1 &call,
                             const parametermap &parameters,
                             string &answer,
                             std::unique_ptr<Mastodon::API::http> &ptr);

    /*!
     *  @brief  Make a streaming GET request.
     *
     *  @param  call      A call defined in Mastodon::API::v1
     *  @param  answer    The answer from the server. Events with JSON-payload.
     *  @param  ptr       Pointer to the http object. Can be used to call
     *                    ptr->cancel_stream()
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t get_stream(const Mastodon::API::v1 &call,
                             string &answer,
                             std::unique_ptr<Mastodon::API::http> &ptr);

    /*!
     *  @brief  Make a streaming GET request.
     *
     *  @param  call      String in the form `/api/v1/example`
     *  @param  answer    The answer from the server. Usually JSON. On error an
     *                    empty string.
     *  @param  ptr       Pointer to the http object. Can be used to call
     *                    ptr->cancel_stream()
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t get_stream(const string &call,
                             string &answer,
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
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t patch(const Mastodon::API::v1 &call,
                        const parametermap &parameters,
                        string &answer);

    /*!
     *  @brief  Make a POST request which doesn't require parameters.
     *
     *  @param  call    A call defined in Mastodon::API::v1
     *  @param  answer  The answer from the server. Usually JSON. On error an
     *                  empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t post(const Mastodon::API::v1 &call, string &answer);

    /*!
     *  @brief  Make a POST request which requires parameters.
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
     *  
     *  @since  before 0.11.0
     */
     uint_fast16_t post(const Mastodon::API::v1 &call,
                        const parametermap &parameters,
                        string &answer);

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
     *  
     *  @since  before 0.11.0
     */
     uint_fast16_t post(const string &call,
                        const parametermap &parameters,
                        string &answer);

    /*!
     *  @brief  Make a PUT request which requires a parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A Mastodon::API::parametermap containing
     *                      parameters
     *  @param  answer      The answer from the server. Usually JSON. On error
     *                      an empty string.
     *
     *  @return @ref error "Error code". If the URL has permanently changed, 13
     *  is returned and answer is set to the new URL.
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t put(const Mastodon::API::v1 &call,
                      const parametermap &parameters,
                      string &answer);

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
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t put(const string &call,
                            const parametermap &parameters,
                            string &answer);

    /*!
     *  @brief  Make a DELETE request which requires parameters.
     *
     *  @param  call        A call defined in Mastodon::API::v1
     *  @param  parameters  A Mastodon::API::parametermap containing parameters
     *
     *  @return @ref error "Error code".
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t del(const Mastodon::API::v1 &call,
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
     *  
     *  @since  before 0.11.0
     */
    uint_fast16_t del(const string &call,
                      const parametermap &parameters,
                      string &answer);

private:
    const string _instance;
    string _access_token;
    string _useragent;
    http _http;
    bool _exceptions;
    string _proxy;
    string _proxy_userpw;

    /*!
     *  @brief  Converts map of parameters into a string.
     *
     *  @param  map         Map of parameters
     *  @param  firstparam  Contains this map the first parameter?
     *
     *  @return String of parameters
     */
    const string maptostr(const parametermap &map,
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
