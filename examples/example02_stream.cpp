// This file is part of mastodon-cpp.
// Listen to /api/v1/streaming/public and display the events.

// Don't compile this if the Easy-interface is turned off
#ifndef WITHOUT_EASY

#include <iostream>
#include <string>
#include <cstdint>
#include <mutex>
#include <chrono>
#include <vector>
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
using std::uint8_t;
using namespace Mastodon;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " <instance>\n";
        return 1;
    }

    // Construct a Mastodon::Easy object without authorization token.
    Easy::API masto(argv[1], "");
    //  Prepare a pointer to the http object, to cancel the stream later.
    std::unique_ptr<API::http> ptr;
    // This variable is filled with the stream data.
    string stream;

    // Get the public timeline, the pointer is set here. The error detection is
    // not very reliable at the moment, don't count on it.
    uint8_t ret = masto.get_stream(API::v1::streaming_public, ptr, stream);
    cout << "Return code: " << std::to_string(ret) << endl;

    // Listen to the stream for 120 seconds.
    for (uint8_t counter = 0; counter < 120; ++counter)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Acquire lock for the stream variable to avoid simultaneous access.
        std::lock_guard<std::mutex> lock(ptr->get_mutex());
        // Parse event stream into a vector.
        std::vector<Easy::stream_event> events = Easy::parse_stream(stream);
        // Clear the stream buffer.
        stream.clear();

        for (const Easy::stream_event &event : events)
        {
            // Print out some information about the events.
            switch (event.type)
            {
            case Easy::event_type::Update:
            {
                Easy::Status status(event.data);
                cout << "[" << status.created_at().strtime("%T") << "] ";
                cout << "Status from: " << status.account().acct()
                     << " (" << status.url() << ")\n";
                break;
            }
            case Easy::event_type::Notification:
            {
                Easy::Notification notification(event.data);
                cout << "Notification involving: "
                     << notification.account().acct()
                     << " (" << notification.id() << ")\n";
                break;
            }
            case Easy::event_type::Delete:
            {
                cout << "Deleted: " << event.data << '\n';
                break;
            }
            default:
            {
                cout << "Something undefined happened. 😱\n";
            }
            }
        }
    }

    // Close connection.
    ptr->cancel_stream();

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
