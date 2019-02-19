/*  This file is part of mastodon-cpp.
 *  Streaming API example
 */


#include <iostream>
#include <string>
#include <cstdint>
#include <thread>
#include <chrono>
#include <memory>
#include <mutex>
#ifdef MASTODON_CPP
    #include "mastodon-cpp.hpp"
#else
    #include <mastodon-cpp/mastodon-cpp.hpp>
#endif

using Mastodon::API;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access_token>\n";
        return 1;
    }

    static std::string answer;
    static std::unique_ptr<Mastodon::API::http> ptr;

    std::cout << "Dumping public timeline...\n";
    std::thread pub([=]
    {
        Mastodon::API masto(argv[1], argv[2]);
        masto.set_useragent("mastodon-cpp-example/1.3.3.7");
        masto.get_stream(API::v1::streaming_public, answer, ptr);
    });
    
    std::uint8_t counter = 0;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (ptr != nullptr)
        {
            std::lock_guard<std::mutex> lock(ptr->get_mutex());
            ++counter;
            std::cout << answer;
            answer.clear();
            if (counter == 10)
            {
                std::cerr << "Cancelling...\n";
                ptr->cancel_stream();
                break;
            }
        }
    }
    pub.join();
    std::cout << '\n';

    std::cout << "Dumping the #np tag...\n";
    answer = "";
    std::thread tag([=]
    {
        Mastodon::API masto(argv[1], argv[2]);
        masto.set_useragent("mastodon-cpp-example/1.3.3.7");
        masto.get_stream(API::v1::streaming_hashtag, {{ "hashtag", {"np"} }},
                         answer, ptr);
    });
    std::this_thread::sleep_for(std::chrono::seconds(20));
    ptr->cancel_stream();
    std::cout << answer;
    std::cout << '\n';
    tag.join();

    return 0;
}