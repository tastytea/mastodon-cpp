/*  This file is part of mastodon-cpp.
 *  Get fields from own account.
 */

// Don't compile this if the Easy-interface is turned off
#ifndef WITHOUT_EASY

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/all.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/all.hpp>
#endif

using std::cout;
using Mastodon::API;
using Mastodon::Easy;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Easy masto(argv[1], argv[2]);
    std::string answer;
    std::uint16_t ret;
    ret = masto.get(API::v1::accounts_verify_credentials, answer);

    cout << "Return code: " << ret << '\n';

    Easy::Account account(answer);
    std::vector<Easy::Account::fields_pair> fields(account.fields());

    for (const auto &field : fields)
    {
        cout << "Name: " << field.first << "\nValue: " << field.second << "\n\n";
    }

    return 0;
}

#else
#include <cstdio>
int main()
{
    printf("mastodon-cpp was compiled without Easy support.\n");
    return 255;
}
#endif  // WITHOUT_EASY
