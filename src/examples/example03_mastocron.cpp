/*  This file is part of mastodon-cpp.
 *  Prints the new toots under a hashtag, designed to be used in cronjobs
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <regex>
#include <cstdlib>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "../mastodon-cpp.hpp"

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
    Json::Value config;
    string lastid = "0";
    string filename = string(getenv("HOME")) + "/.config/mastocron.json";

    // Read config file, get last seen toot-id
    try {
        Json::Reader reader;
        std::ifstream file(filename, std::ifstream::binary);
        file >> config;
        lastid = config.get(hashtag, "0").asString();
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

            Json::Value tree;
            Json::Reader reader;
            
            reader.parse(answer, tree);
            for (const auto &toot : tree)
            {
                string content = toot["content"].asString();
                std::regex reparagraph("</p><p>");
                std::regex restrip("<[^>]*>");

                cout << "++++++++\n";
                content = std::regex_replace(content, reparagraph, "\n\n");
                cout << std::regex_replace(content, restrip, "") << '\n';
                cout << "  – ";
                cout << toot["account"]["display_name"].asString()
                     << " (" << toot["account"]["acct"] << ") at "
                     << toot["created_at"].asString() << "\n";
                cout << "    " << toot["url"].asString() << '\n';
                for (const auto &media : toot["media_attachments"])
                {
                    cout << "Attachment: <" << media["url"].asString() << ">\n";
                }
                cout << "++++++++\n";
            }

            // Write the id of the newest toot in the config file
            lastid = tree[0]["id"].asString();
            config[hashtag] = lastid;

            Json::StyledWriter writer;
            const string output = writer.write(config);
            std::ofstream outfile(filename);
            if (outfile.is_open())
            {
                outfile.write(output.c_str(), output.length());
                outfile.close();
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
