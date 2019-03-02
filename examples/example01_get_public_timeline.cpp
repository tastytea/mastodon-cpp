/*  This file is part of mastodon-cpp.
 */

// Don't compile this if the Easy-interface is turned off
#ifndef WITHOUT_EASY

#include <iostream>
#include <string>
#include <cstdint>
#include <regex>
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/all.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    #include <mastodon-cpp/easy/all.hpp>
#endif

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::uint16_t;
using namespace Mastodon;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " <instance>\n";
        return 1;
    }

    // Construct a Mastodon::Easy object without authorization token.
    Easy masto(argv[1], "");
    // Retrieve the last 4 local statuses.
    return_call ret = masto.get(API::v1::timelines_public,
                                {
                                    { "local", { "true" }},
                                    { "limit", { "4" }}
                                });
    // If no error was returned.
    if (ret)
    {
        // Convert answer to vector of strings, loop through vector.
        for (const string &strstatus : Easy::json_array_to_vector(ret.answer))
        {
            // Construct mastodon::Easy::Status from string.
            Easy::Status status(strstatus);
            string content = status.content();
            std::regex re_html("<[^>]+>");

            // Remove HTML tags from status content.
            content = std::regex_replace(content, re_html, "");
            // Print account and content.
            cout << "  " << status.account().acct() << " wrote:\n";
            cout << content << endl << endl;
        }
    }
    else
    {
        // Print error message.
        cerr << ret.error_message << endl;
        // Print HTTP status code, if there is one.
        if (ret.http_error_code != 0)
        {
            cerr << "HTTP status code: "
                 << std::to_string(ret.http_error_code) << endl;
        }
        return ret.error_code;
    }

    return 0;
}

#else
#include <cstdio>
int main()
{
    std::printf("mastodon-cpp was compiled without Easy support.\n");
    return 255;
}
#endif  // WITHOUT_EASY
