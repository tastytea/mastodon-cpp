/*  This file is part of mastodon-cpp.
 *  This example dumps the raw JSON of your last toot with media attached
 *  and your last 2 followers.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using Mastodon::API;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], argv[2]);
    masto.set_useragent("mastodon-cpp-example/1.3.3.7");
    std::string answer;
    std::uint16_t ret;

    ret = masto.get(API::v1::accounts_verify_credentials, answer);
    if (ret == 0)
    {
        std::cout << "Your last toot with media attached:\n";
        std::string uid = answer.substr(7, answer.find("\"", 7) - 7);
        API::parametermap parameters =
        {
            { "id", { uid } },
            { "limit", { "1" } },
            { "only_media", { "1" } }
        };

        ret = masto.get(API::v1::accounts_id_statuses, parameters, answer);
        if (ret == 0)
        {
            std::cout << answer << '\n';
        }
        else
        {
            std::cerr << "Error code: " << ret << '\n';
            return ret;
        }

        std::cout << "\nYour last 2 followers:\n";
        parameters =
        {
            {
                "limit", { "2" }
            },
            {
                "exclude_types", { "favourite", "reblog", "mention" }
            }
        };
        ret = masto.get(API::v1::notifications, parameters, answer);
        if (ret == 0)
        {
            std::cout << answer << '\n';
            return 0;
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
                     "New URL: " << answer << '\n';
        return ret;
    }
    else
    {
        std::cerr << "Error code: " << ret << '\n';
        return ret;
    }

    return 0;
}
