/*  This file is part of mastodon-cpp.
 */

#include <iostream>
#include <cstdint>
#include "mastodon-cpp.hpp"

int main(int argc, char *argv[])
{
    Mastodon::API test("soc.ialis.me", "");
    std::string answer;
    std::uint16_t ret = test.get(Mastodon::API::v1::instance, answer);
    if (ret == 0)
    {
        if (answer.substr(7, 14) == "\"soc.ialis.me\"")
        {
            return 0;
        }
    }

    std::cout << ret << ": " << answer.substr(7, 14) << '\n';
    return 1;
}
