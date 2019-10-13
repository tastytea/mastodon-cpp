// This file is part of mastodon-cpp.
// Prints shortcode + URL for each custom emoji.

// Don't compile this if the Easy-interface is turned off
#ifndef WITHOUT_EASY

#include <iostream>
#include <string>
#include <vector>
#include "mastodon-cpp.hpp"
#include "easy/all.hpp"

using std::string;
using std::vector;
using namespace Mastodon;

int main(int argc, char *argv[])
{
    const vector<string> args(argv, argv + argc);
    if (args.size() < 2)
    {
        std::cerr << "usage: " << args[0] << " <instance>\n";
        return 1;
    }

    // Construct a Mastodon::Easy object.
    Easy::API masto(args[1], "");
    const return_call ret = masto.get(API::v1::custom_emojis);

    // Convert JSON array into vector of strings.
    for (const string &str : Easy::json_array_to_vector(ret))
    {
        // Construct Emoji object from string.
        const Easy::Emoji emoji(str);
        std::cout << ':' << emoji.shortcode() << ": <" << emoji.url() << ">\n";
    }

    return 0;
}

#else
#include <iostream>
int main()
{
    std::cout << "mastodon-cpp was compiled without Easy support.\n";
    return 255;
}
#endif  // WITHOUT_EASY
