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
#include <cstdint>
#include <iostream>
#include <istream>
#include <ostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "mastodon-cpp.hpp"

using namespace Mastodon;
using std::string;
using std::cerr;

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

API::http::http(const API &api, const string &instance,
                const string &access_token)
: parent(api)
, _instance(instance)
, _access_token(access_token)
, _ctx(ssl::context::tlsv12)
, _resolver(_io_service)
, _socket(_io_service, _ctx)
{
    _ctx.set_options(ssl::context::tlsv12 | ssl::context::tlsv11 |
                    ssl::context::no_sslv3 | ssl::context::no_sslv2 |
                    ssl::context::no_tlsv1);
    _ctx.set_default_verify_paths();
}

const std::uint16_t API::http::request_sync(const method &meth,
                                            const string &path,
                                            string &answer)
{
    return request_sync(meth, path, "", answer);
}

const std::uint16_t API::http::request_sync(const method &meth,
                                            const string &path,
                                            const string &data,
                                            string &answer)
{
    try
    {
        tcp::resolver::query query(_instance, "https");
        tcp::resolver::iterator endpoint_iterator = _resolver.resolve(query);
        boost::asio::connect(_socket.lowest_layer(), endpoint_iterator);
        _socket.lowest_layer().set_option(tcp::no_delay(true));
        // Server Name Indication (SNI)
        SSL_set_tlsext_host_name(_socket.native_handle(), _instance.c_str());

        _socket.set_verify_mode(ssl::verify_peer);
        _socket.set_verify_callback(ssl::rfc2818_verification(_instance));

        _socket.handshake(ssl_socket::client);

        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        switch (meth)
        {
            case http::method::GET:
                request_stream << "GET";
                request_stream << " " << path;
                break;
            // case http::method::PATCH:
            //     request_stream << "PATCH";
            //     break;
            // case http::method::POST:
            //     request_stream << "POST";
            //     break;
            // case http::method::DELETE:
            //     request_stream << "DELETE";
            //     break;
                default:
                    cerr << "NOT IMPLEMENTED\n";
                    return 0xffff;
        }
        request_stream << " HTTP/1.0\r\n";
        request_stream << "Host: " << _instance << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n";
        request_stream << "User-Agent: " << parent.get_useragent() << "\r\n";
        request_stream << "Authorization: Bearer "
                       << _access_token << "\r\n\r\n";
        boost::asio::write(_socket, request);

        boost::asio::streambuf response;
        boost::asio::read_until(_socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        std::uint16_t status_code;
        std::string status_message;
        response_stream >> http_version;
        response_stream >> status_code;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            cerr << "Invalid response\n";
            return 0xffff;
        }
        if (status_code != 200)
        {
            cerr << "Response returned with status code " << status_code
                 << ": " << status_message << "\n";
            return 0xffff;
        }

        // Read headers
        boost::asio::read_until(_socket, response, "\r\n\r\n");
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
        {}
        //response.consume(response.size());

        // Read body
        boost::system::error_code error;
        answer = "";
        std::ostringstream ss;
        while (boost::asio::read(_socket, response,
                                 boost::asio::transfer_at_least(1), error))
        {
            ss << &response;
        }
        if (error != boost::asio::error::eof)
        {
            throw boost::system::system_error(error);
        }
        answer = ss.str();
    }
    catch (const std::exception &e)
    {
        cerr << "Exception: " << e.what() << "\n";
        return 0xffff;
    }

    return 0;
}
