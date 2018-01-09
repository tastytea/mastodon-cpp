/*  This file is part of mastodon-cpp.
 */

#include <iostream>
#include "../mastodon-cpp.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], argv[2]);

    std::cout << masto.get(Mastodon::API::v1::accounts_id,
                           "44897") << '\n';
}
