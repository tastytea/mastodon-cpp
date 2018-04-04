/*  This file is part of mastodon-cpp.
 *  Prints a Mastodon-conversation in a tree.
 *  Argument has to be in the form: https://<domain>/<user>/<status id>
 *  
 *  This example uses a rather wasteful approach in order to use less code and
 *  therefore be more clear. Please don't use it on long conversations.
 */

// Don't compile this if the Easy-interface is turned off
#ifndef WITHOUT_EASY

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include <regex>

// If we are compiling mastodon-cpp, use another include path
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
    #include "easy/all.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
    // Include all headers in mastodon-cpp/easy/
    #include <mastodon-cpp/easy/all.hpp>
#endif

using Mastodon::API;
using Mastodon::Easy;
using std::cout;
using std::chrono::system_clock;

// Transform time_point into a string with the local time
std::string get_localtime(const system_clock::time_point &timepoint)
{
    std::time_t time = system_clock::to_time_t(timepoint);
    std::tm *timeinfo = std::localtime(&time);
    char buffer[9];

    std::strftime(buffer, 9, "%T", timeinfo);

    return buffer;
}

// Print a status to stdout, nicely formatted
void format_status(const Easy::Status &status, const std::uint8_t &level)
{
    std::string space(level, ' ');
    // Remove HTML-tags
    std::regex restrip("<[^>]*>");
    std::string content = std::regex_replace(status.content(), restrip, "");

    cout << space << "+-----------------------------------------\n";
    cout << space << "| " << status.account().acct() << ": \n";

    while (!content.empty())
    {
        cout << space << "| " << content.substr(0, 40) << '\n';
        if (content.length() > 40)
        {
            content = content.substr(40);
        }
        else
        {
            content.clear();
        }
    }
    cout << space << "|                                 "
         << get_localtime(status.created_at()) << '\n';
    cout << space << "+-----------------------------------------" << std::endl;
}

// Fetch status and its descendants, output them
std::uint16_t print_status(Easy &masto, const std::string &id,
                           const std::uint8_t level)
{
    std::uint16_t ret;
    std::string answer;

    ret = masto.get(Mastodon::API::v1::statuses_id, id, answer);

    if (ret == 0)
    {
        format_status(Easy::Status(answer), level);

        ret = masto.get(Mastodon::API::v1::statuses_id_context, id, answer);
        if (ret == 0)
        {
            Easy::Context context(answer);
            for (const Easy::Status &s : context.descendants())
            {
                // Only print descendant if it is a direct reply
                // NOTE: This is a wasteful approach, I use it only in the
                //       interest of more clarity. Don't do this at home. :-)
                if (s.in_reply_to_id() == std::stoull(id))
                {
                    print_status(masto, std::to_string(s.id()), level + 4);
                }
            }
        }
    }

    return ret;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " <url>\n";
        return 1;
    }

    // Extract domain name
    std::string instance = std::string(argv[1]);
    std::size_t pos = instance.find('/') + 2;
    instance = instance.substr(pos, instance.find('/', pos) - pos);

    // Extract status ID
    std::string id = std::string(argv[1]);
    id = id.substr(id.rfind('/') + 1);

    cout << " Instance: " << instance << "\nStatus ID: " << id << "\n\n";

    Easy masto(instance, "");
    return print_status(masto, id, 0);
}

#else
int main()
{
    printf("mastodon-cpp was compiled without Easy support.\n");
    return 255;
}
#endif  // WITHOUT_EASY
