/*  This file is part of mastodon-cpp.
 *  Post a status, then delete it.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <chrono>
#include <thread>
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using Mastodon::API;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], argv[2]);
    masto.set_useragent("mastodon-cpp-example/1.3.3.7");
    std::string answer;
    std::uint16_t ret;
    std::string toot;
    std::string id;

    std::cout << "Toot: ";
    std::cin >> toot;

    API::parametermap parameters =
    {
        { "status", { toot } },
        { "visibility", { "unlisted" } },
        { "spoiler_text", { "test" } }
    };
    ret = masto.post(API::v1::statuses, parameters, answer);
    if (ret == 0)
    {
        id = answer.substr(7, answer.find("\"", 7) - 7);

        std::cout << "Deleting in 30 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(30));
        ret = masto.del(API::v1::statuses_id, {{"id", {id}}});
        if (ret == 0)
        {
            std::cout << "Status " << id << " deleted.\n";
        }
        else
        {
            std::cerr << "Error code: " << ret << '\n';
            return ret;
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
