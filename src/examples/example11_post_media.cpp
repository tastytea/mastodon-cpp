/*  This file is part of mastodon-cpp.
 *  Post the same media 2 times, with URLs
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <jsoncpp/json/json.h>
#include "mastodon-cpp/mastodon-cpp.hpp"

using Mastodon::API;

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
    Json::Value json;
    std::uint16_t ret;
    std::string filepath;

    std::cout << "Absolute filename: ";
    std::cin >> filepath;

    API::parametermap parameters =
    {
        { "file", { filepath } }
    };
    ret = masto.post(API::v1::media, parameters, answer);
    if (ret == 0)
    {
        ss.str(answer);
        ss >> json;
        std::string image1_id = json["id"].asString();
        std::string image1_url = json["url"].asString();
        parameters =
        {
            { "file", { filepath } }
        };
        ret = masto.post(API::v1::media, parameters, answer);
        if (ret == 0)
        {
            ss.str(answer);
            ss >> json;
            std::string image2_id = json["id"].asString();
            std::string image2_url = json["url"].asString();
            parameters =
            {
                { "status", { image1_url + " \n" + image2_url } },
                { "media_ids", { image1_id, image2_id } },
                { "visibility", { "direct" } }
            };
            ret = masto.post(API::v1::statuses, parameters, answer);
            if (ret == 0)
            {
                return 0;
            }
        }
    }
    else if (ret == 13)
    {
        std::cerr << "The URL has permanently changed.\n" <<
                     "New URL: " << answer << '\n';
        return ret;
    }

    std::cout << answer << '\n';
    std::cerr << "Error code: " << ret << '\n';
    return ret;
}
