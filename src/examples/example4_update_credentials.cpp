/*  This file is part of mastodon-cpp.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "../mastodon-cpp.hpp"

using Mastodon::API;

int main(int argc, char *argv[])
{
    std::cerr << "Doesn't work yet. :-(\n";
    return 2;

    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], argv[2]);
    masto.set_useragent("mastodon-cpp-example/1.3.3.7");
    std::string answer;
    std::uint16_t ret;

    API::parametermap params =
    {
        { "display_name", { "Botty McBotface" } },
        // { "note", { "Beep Bop." } }
    };
    
    ret = masto.patch(API::v1::accounts_update_credentials, params, answer);
    if (ret == 0)
    {
        std::cout << answer << '\n';
    }
    else
    {
        std::cerr << "Error code: " << ret << '\n';
        return ret;
    }

    return 0;
}
