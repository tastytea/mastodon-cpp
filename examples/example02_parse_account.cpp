/*  This file is part of mastodon-cpp.
 *  This example parses your account data and prints it out in a readable way.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <jsoncpp/json/json.h>
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using Mastodon::API;
using std::cout;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], argv[2]);
    std::string answer;
    std::stringstream ss;
    std::uint16_t ret;

    ret = masto.get(API::v1::accounts_verify_credentials, answer);
    if (ret == 0)
    {
        ss.str(answer);
        Json::Value json;
        ss >> json;

        std::string uid = json["id"].asString();
        cout << "Your ID is: " << uid << '\n';
        cout << "Your whole acount tree:\n";
        
        for (auto it = json.begin(); it != json.end(); ++it)
        {
            if (it.name().compare("source") == 0)
            {
                cout << it.name() << '\n';
                for (auto it_s = (*it).begin(); it_s != (*it).end(); ++it_s)
                {
                    cout << '\t' << it_s.name() << ": ";
                    cout << *it_s << '\n';
                }
            }
            else
            {
                cout << it.name() << ": ";
                cout << *it << '\n';
            }
        }
    }
    else if (ret == 13)
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
