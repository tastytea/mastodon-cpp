/*  This file is part of mastodon-cpp.
 *  In this example we look at HTTP headers to determine how many calls we are
 *  allowed to make.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "../mastodon-cpp.hpp"

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
        std::string remaining = masto.get_header("X-RateLimit-Remaining");
        std::string reset = masto.get_header("X-RateLimit-Reset");
        std::cout << "You are allowed to make " << remaining
                  << " calls until the counter is reset at " << reset << '\n';

        if (std::stoi(remaining) <= 1)
        {
            std::cout << "🔥 Please let the server cool off a bit! 🔥\n";
        }
    }
    else if (ret == 3)
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
