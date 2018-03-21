/*  This file is part of mastodon-cpp.
 *  Simplify the interface
 */


#include <iostream>
#include <string>
#include <cstdint>
#include "mastodon-cpp/mastodon-cpp.hpp"

using Mastodon::API;

class EasyToot : public Mastodon::API
{
public:
    explicit EasyToot(const std::string &instance, const std::string &access_token)
    : API(instance, access_token)
    {}

    std::uint16_t toot(const std::string &text, const std::string &cw = "")
    {
        std::string answer;
        API::parametermap parameters;
        parameters.insert({ "status", { text } } );
        if (!cw.empty())
        {
            parameters.insert({ "spoiler_text", { cw } } );
        }

        return post(API::v1::statuses, parameters, answer);
    }
};

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access_token>\n";
        return 1;
    }

    std::string answer;
    std::uint16_t ret = 0;
    EasyToot masto(argv[1], argv[2]);

    masto.toot("Test");
    if (ret != 0)
    {
        std::cerr << "Error: " << ret << '\n';
    }

    return ret;
}
