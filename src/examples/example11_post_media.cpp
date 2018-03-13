/*  This file is part of mastodon-cpp.
 *  Post the same media 2 times, with URLs
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../mastodon-cpp.hpp"

using Mastodon::API;
namespace pt = boost::property_tree;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], argv[2]);
    std::string answer;
    std::istringstream iss;
    pt::ptree tree;
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
        iss.str(answer);
        pt::read_json(iss, tree);
        std::string image1_id = tree.get<std::string>("id");
        std::string image1_url = tree.get<std::string>("url");
        parameters =
        {
            { "file", { filepath } }
        };
        ret = masto.post(API::v1::media, parameters, answer);
        if (ret == 0)
        {
            iss.str(answer);
            pt::read_json(iss, tree);
            std::string image2_id = tree.get<std::string>("id");
            std::string image2_url = tree.get<std::string>("url");
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
