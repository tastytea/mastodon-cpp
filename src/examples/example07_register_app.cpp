/*  This file is part of mastodon-cpp.
 *  Register as an application.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../mastodon-cpp.hpp"

using Mastodon::API;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " <instance>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], "");
    masto.set_useragent("mastodon-cpp-example/1.3.3.7");
    
    std::string answer;
    std::uint16_t ret;
    std::string client_id, client_secret, url;

    ret = masto.register_app1(argv[1],
                              "test123",
                              "urn:ietf:wg:oauth:2.0:oob",
                              "read follow",
                              "",
                              client_id,
                              client_secret,
                              url);
    if (ret == 0)
    {
        std::cout << "Visit " << url << " to get the code.\n";

        std::string code;
        std::cout << "Insert code: ";
        std::cin >> code;

        std::string access_token;
        ret = masto.register_app2(argv[1],
                                  client_id,
                                  client_secret,
                                  "urn:ietf:wg:oauth:2.0:oob",
                                  code,
                                  access_token);
        if (ret == 0)
        {
            std::cout << "Success!\nAccess-token: " << access_token << '\n';
            std::cout << "Testing access token...\n";
            ret = masto.get(API::v1::accounts_verify_credentials, answer);
            if (ret == 0)
            {
                std::cout << answer;
            }
            else
            {
                std::cerr << "Error code: " << ret << '\n';
                return ret;
            }
        }
        else
        {
            std::cerr << "Error code: " << ret << '\n';
            return ret;
        }
    }
    else if (ret == 13)
    {
        std::cerr << "The URL has permanently changed.\n" <<
                     "New URL: " << url << '\n';
        return ret;
    }
    else
    {
        std::cerr << "Error code: " << ret << '\n';
        return ret;
    }

    return 0;
}
