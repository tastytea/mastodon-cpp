// This file is part of mastodon-cpp.
// Get 2 pages of 5 favourites each.

// Don't compile this if the Easy-interface is turned off
#ifndef WITHOUT_EASY

#include <iostream>
#include <string>
#include <vector>
#include "mastodon-cpp.hpp"
#include "easy/all.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using namespace Mastodon;

void print_favs(Easy::API &masto, const string &max_id = "")
{
    // Set up parameters.
    Mastodon::parameters params =
        {
            { "limit", { "5" } },
            { "exclude_types", { "follow", "reblog", "mention" } }
        };
    // Set max_id if given.
    if (!max_id.empty())
    {
        params.push_back({ "max_id", { max_id } });
    }

    // Retrieve the last 5 favourites.
    return_call ret = masto.get(API::v1::notifications, params);
    // If no error was returned.
    if (ret)
    {
        // Convert answer to vector of strings, loop through vector.
        for (const string &str : Easy::json_array_to_vector(ret.answer))
        {
            // Construct Mastodon::Easy::Notification from string.
            const Easy::Notification notif(str);
            cout << notif.created_at().strtime("%F %T: ");
            cout << notif.account().display_name() << " favourited a status.\n";
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
    }
}

int main(int argc, char *argv[])
{
    const vector<string> args(argv, argv + argc);
    if (args.size() < 3)
    {
        std::cerr << "usage: " << args[0] << " <instance> <auth token>\n";
        return 1;
    }

    // Construct a Mastodon::Easy object.
    Easy::API masto(args[1], args[2]);
    print_favs(masto);

    cout << "\nLink header is: " << masto.get_header("link") << "\n\n";

    // Get the max_id for pagination.
    // See <https://docs.joinmastodon.org/api/rest/notifications/#pagination>
    print_favs(masto, masto.get_link().max_id());
    // The same: print_favs(masto, masto.get_link().next());

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
