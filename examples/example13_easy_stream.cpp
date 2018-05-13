/*  This file is part of mastodon-cpp.
 *  Prints some information from the public timeline.
 */

// Don't compile this if the Easy-interface is turned off
#ifndef WITHOUT_EASY

#include <iostream>
#include <string>
#include <thread>
#include <memory>
#include <vector>
#include <chrono>

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

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    cout << "I'll show you the public timeline. Press CTRL-C to cancel\n";

    // These have to be static in order to use them in- and outside the thread
    static std::string stream;
    // You can cancel the stream with this pointer (ptr->cancel_stream())
    static std::unique_ptr<Mastodon::API::http> ptr;

    // Start a new thread for the stream
    std::thread pub_tl([=]
    {
        Easy masto(argv[1], argv[2]);
        masto.get_stream(Mastodon::API::v1::streaming_public, stream, ptr);
    });

    while (true)
    {
        // Parse event stream and clear it afterwards
        std::vector<Easy::stream_event> events = Easy::parse_stream(stream);
        stream.clear();

        // The contents of the stream are now in a vector of pairs
        // { Easy::event_type, std::string }
        for (const Easy::stream_event &event : events)
        {
            Easy::Status status;
            Easy::Notification notification;

            // Print out some information about the events
            switch (event.first)
            {
                case Easy::event_type::Update:
                    status.from_string(event.second);
                    cout << "[" <<
                        Easy::strtime_local(status.created_at(), "%T") << "] ";
                    cout << "Status from: " << status.account().acct()
                         << " (" << status.url() << ")\n";
                    break;
                case Easy::event_type::Notification:
                    notification.from_string(event.second);
                    cout << "Notification involving: "
                         << notification.account().acct()
                         << " (" << notification.id() << ")\n";
                    break;
                case Easy::event_type::Delete:
                    cout << "Deleted: " << event.second << '\n';
                    break;
                default:
                    cout << "Something undefined happened. 😱\n";
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    pub_tl.join();
}

#else
int main()
{
    printf("mastodon-cpp was compiled without Easy support.\n");
    return 255;
}
#endif  // WITHOUT_EASY
