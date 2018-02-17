/*  This file is part of mastodon-cpp.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <chrono>
#include <thread>
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
    masto.set_useragent("mastodon-cpp-example/1.3.3.7");
    std::string answer;
    std::uint16_t ret;
    std::string id;

    std::cout << "Follow [ID or username@domain]: ";
    std::cin >> id;

    // If no @ is found, it is presumably an ID
    if (id.find('@') == std::string::npos)
    {
        ret = masto.post(API::v1::accounts_id_follow, id, answer);
        if (ret == 0)
        {
            // std::cout << answer << '\n';
        }
        else if (ret == 3)
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

        std::cout << "Unfollowing in 30 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(30));
        ret = masto.post(API::v1::accounts_id_unfollow, id, answer);
        if (ret == 0)
        {
            // std::cout << answer << '\n';
        }
        else
        {
            std::cerr << "Error code: " << ret << '\n';
            return ret;
        }
    }
    else
    {
        API::parametermap params =
        {
            { "uri", { id } }
        };
        ret = masto.post(API::v1::follows, params, answer);
        if (ret == 0)
        {
            // std::cout << answer << '\n';
            id = answer.substr(7, answer.find("\"", 7) - 7);
        }
        else
        {
            std::cerr << "Error code: " << ret << '\n';
            return ret;
        }

        std::cout << "Unfollowing " << id << " in 30 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(30));
        ret = masto.post(API::v1::accounts_id_unfollow, id, answer);
        if (ret == 0)
        {
            // std::cout << answer << '\n';
        }
        else
        {
            std::cerr << "Error code: " << ret << '\n';
            return ret;
        }
    }

    return 0;
}
