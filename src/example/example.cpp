/*  This file is part of mastodon-cpp.
 */

#include <iostream>
#include <vector>
#include <string>
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

    std::vector<std::string> parameters =
    {
        "limit=2",
        "only_media=1"
    };
    std::cout << 
        masto.get(API::v1::accounts_id_statuses, "44897", parameters) <<
        '\n';
}
