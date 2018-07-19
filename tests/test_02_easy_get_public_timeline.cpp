/*  This file is part of mastodon-cpp.
 */

// Don't compile this if the Easy-interface is turned off
#ifndef WITHOUT_EASY

#include <iostream>
#include <cstdint>
#include "mastodon-cpp.hpp"
#include "easy/easy.hpp"
#include "easy/entities/status.hpp"

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

#else
#include <cstdio>
int main()
{
    printf("mastodon-cpp was compiled without Easy support.\n");
    return 0;
}
#endif  // WITHOUT_EASY
