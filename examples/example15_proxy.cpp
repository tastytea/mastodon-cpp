/*  This file is part of mastodon-cpp.
 *  This example shows how to use a proxy.
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

using std::cout;
using Mastodon::API;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], argv[2]);
    // SOCKS5 Proxy. Proxy resolves URL hostname.
    masto.set_proxy("socks5h://[fd12::1a]:1080/");
    // HTTPS proxy with username and password
    masto.set_proxy("https://localhost:3128", "user5:supersecurepassword");
    std::string answer;
    std::uint16_t ret;

    ret = masto.get(API::v1::accounts_verify_credentials, answer);

    cout << "Return code: " << ret << '\n';
    std::cout << answer << '\n';

    return 0;
}
