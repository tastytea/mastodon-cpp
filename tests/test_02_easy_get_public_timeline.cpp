/*  This file is part of mastodon-cpp.
 */

#include <iostream>
#include <cstdint>
#include "mastodon-cpp.hpp"
#include "easy/easy.hpp"
#include "easy/status.hpp"

int main(int argc, char *argv[])
{
    Mastodon::Easy test("botsin.space", "");
    std::string answer;
    std::uint16_t ret = test.get(Mastodon::API::v1::timelines_public,
                                 { { "limit", { "1" } } }, answer);
    if (ret == 0)
    {
        Mastodon::Easy::Status status(answer);
        if (status.valid())
        {
            return 0;
        }
    }

    std::cout << ret << ": " << answer << '\n';
    return 1;
}
