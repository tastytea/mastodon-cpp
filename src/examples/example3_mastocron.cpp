/*  This file is part of mastodon-cpp.
 *  Prints the new toots under a hashtag, designed to be used in cronjobs
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <regex>
#include <cstdlib>
#include "../mastodon-cpp.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;
using Mastodon::API;
using std::cout;
using std::string;

int main(int argc, char *argv[])
{
    string limit = "20";
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <hashtag> [limit]\n";
        std::cerr << "  Default limit is 20, max limit is 40.\n";
        return 1;
    }
    else if (argc == 4)
    {
        limit = argv[3];
    }

    Mastodon::API masto(argv[1], "");
    string hashtag = argv[2];
    string answer;
    std::uint16_t ret;
    pt::ptree config;
    string lastid = "0";
    string filename = string(getenv("HOME")) + "/.config/mastocron.json";

    // Read config file, get last seen toot-id
    try {
        pt::read_json(filename, config);
        lastid = config.get(hashtag, "0");
    }
    catch (std::exception &e)
    {
        // most likely no config file found, ignore
    }

    // Only get toots we haven't seen yet
    API::parametermap params =
    {
        { "limit", { limit } },
        { "since_id", { lastid } }
    };
    ret = masto.get(API::v1::timelines_tag_hashtag, hashtag, params, answer);

    if (ret == 0)
    {
        // If answer is empty, there are no new toots,
        // if answer is "[]" there are none at all
        if (answer != "" && answer != "[]")
        {
            string ornament = "  +++++";
            for (std::uint8_t i = hashtag.size(); i > 0; --i)
            {
                ornament += "+";
            }
            cout << ornament << '\n';
            cout << "  + " << hashtag << ": +\n";
            cout << ornament << '\n';

            std::istringstream iss(answer);
            pt::ptree tree;
            
            pt::read_json(iss, tree);
            for (const pt::ptree::value_type &toot : tree.get_child(""))
            {
                string content = toot.second.get<string>("content");
                std::regex reparagraph("</p><p>");
                std::regex restrip("<[^>]*>");

                cout << "++++++++\n";
                content = std::regex_replace(content, reparagraph, "\n\n");
                cout << std::regex_replace(content, restrip, "") << '\n';
                cout << "  – ";
                cout << toot.second.get<string>("account.display_name")
                     << " (" << toot.second.get<string>("account.acct") << ") at "
                     << toot.second.get<string>("created_at") << "\n";
                cout << "    " << toot.second.get<string>("url") << '\n';
                for (const pt::ptree::value_type &media : toot.second.get_child("media_attachments"))
                {
                    cout << "Attachment: <" << media.second.get<string>("url") << ">\n";
                }
                cout << "++++++++\n";
            }

            // Write the id of the newest toot in the config file
            lastid = tree.front().second.get<string>("id");
            config.put(hashtag, lastid);
            pt::write_json(filename, config);
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
