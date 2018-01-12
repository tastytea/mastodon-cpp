/*  This file is part of mastodon-cpp.
 */

#include <iostream>
#include "../mastodon-cpp.hpp"

int main(int argc, char *argv[])
{
    Mastodon::API test("soc.ialis.me", "");
    std::string answer = test.get(Mastodon::API::v1::instance);

    if (answer.substr(7, 14) == "\"soc.ialis.me\"")
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
