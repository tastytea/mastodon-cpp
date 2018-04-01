/*  This file is part of mastodon-cpp.
 */

// Don't compile this if the Easy-interface is turned off
#ifndef WITHOUT_EASY

#include <iostream>
#include <string>
#include <cstdint>

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

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Easy masto(argv[1], argv[2]);
    std::string answer;
    std::uint16_t ret;

    // Get own account in order to obtain account ID
    ret = masto.get(API::v1::accounts_verify_credentials, answer);
    if (ret == 0)
    {
        // Construct an Account object using the JSON string from the server
        Easy::Account acc(answer);

        // Get last status
        ret = masto.get(API::v1::accounts_id_statuses,
                        std::to_string(acc.id()),
                        {{ "limit", { "1" } }},
                        answer);
        if (ret == 0)
        {
            // answer contains an array with a single object. This works because
            // Easy::Status will turn that into an object, but an array with
            // more than 1 object will not work.
            Easy::Status status(answer);

            // An Entitiy is valid if the JSON was not empty and contained no
            // "error":-key
            if (status.valid())
            {
                if (!status.language().empty())
                    cout << "Language: " << status.language() << '\n';
                if (!status.content().empty())
                    cout << "Content: "
                         << status.content().substr(0, 200) << "…\n";
                if (!status.application().name().empty())
                    cout << "Application used: "
                         << status.application().name() << '\n';
                cout << "ID: " << status.id() << '\n';

                string acct;
                string url;
                std::vector<Easy::Attachment> attachments;
                std::vector<Easy::Tag> tags;
                // If the status is a reblog, print the original author
                if (status.reblog().valid())
                {
                    // status.reblog() is an Easy::Status
                    // status.reblog().account() is an Easy::Account
                    cout << "Original ID: " << status.reblog().id() << '\n';
                    acct = status.reblog().account().acct();
                    url = status.reblog().account().url();
                    attachments = status.reblog().media_attachments();
                    tags = status.reblog().tags();
                }
                else
                {
                    acct = status.account().acct();
                    url = status.account().url();
                    attachments = status.media_attachments();
                    tags = status.tags();
                }
                cout << "From: " << acct << " ";
                cout << "(" << url << ")\n";

                // List attachments, if any
                for (const Easy::Attachment &attachment : attachments)
                {
                    cout << "Attachment: " << attachment.text_url()
                         << " (" << attachment.size() << ")\n";
                }

                // List hashtags, if any
                for (const Easy::Tag &tag : tags)
                {
                    cout << "Hashtag: #" << tag.name()
                         << " (" << tag.url() << ")\n";
                }
            }

            return 0;
        }
    }

    std::cout << answer << '\n';
    std::cerr << "Error code: " << ret << '\n';
    return ret;
}

#else
int main()
{
    printf("mastodon-cpp was compiled without Easy support.\n");
    return 255;
}
#endif  // WITHOUT_EASY
