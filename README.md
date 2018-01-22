**mastodon-cpp** is a C++ wrapper for the Mastodon API. The aim is to be as simple as possible.
The library takes care of the network stuff. You submit a query and get the raw JSON.
All versions below 1.0.0 (SOVERSION 0) are considered insecure, unstable and can change any time.

# Install

## Dependencies

 * Tested OS: Linux
 * C++ compiler (tested: gcc 6.4)
 * [cmake](https://cmake.org/) (tested: 3.9.6)
 * [boost](http://www.boost.org/) (tested: 1.63.0)
 * Optional: [doxygen](https://www.stack.nl/~dimitri/doxygen/) (tested: 1.8.13)

## Get sourcecode

### Release

Download the current release at [GitHub](https://github.com/tastytea/mastodon-cpp/releases).

### Development version

    git clone https://github.com/tastytea/mastodon-cpp.git

## Compile

    mkdir build
    cd build/
    cmake ..
    make

cmake options:

 * `-DCMAKE_BUILD_TYPE=Debug` for a debug build
 * `-DWITH_EXAMPLES=ON` if you want to compile the examples
 * `-DWITH_TESTS=ON` if you want to compile the tests
 * `-DWITH_DOC=ON` if you want to compile the HTML reference

You can run the tests with `ctest ..` inside the build directory.
Install with `make install`.

# Usage

The HTML reference can be generated with `build_doc.sh`, if doxygen is installed. Or just look in `src/mastodon-cpp.hpp`. There are examples in `src/examples/`. All input is expected to be UTF-8.

## Most basic example

    #include <iostream>
    #include <string>
    #include <mastodon-cpp.hpp>

    int main()
    {
        Mastodon::API masto("social.example.com", "secret_token");
        std::string answer;
        masto.get(API::v1::accounts_verify_credentials, answer);
        std::cout << answer << '\n';
    }

## Compiling your project

After you did a `make install`, a project consisting of one file can be compiled as follows:

    g++ -std=c++14 -lmastodon-cpp -lboost_system -lssl -lcrypto example.cpp

## Error codes

|      Code | Explanation                   |
| --------: |:------------------------------|
|         0 | No error                      |
|         1 | Invalid call                  |
|         2 | Not implemented               |
|        16 | Connection failed             |
|        17 | TLS error                     |
|        18 | Invalid response from server  |
| 100 - 999 | HTTP status codes             |
|     65535 | Unknown exception             |

If you use a debug build, you get more verbose error messages.

# TODO

 * Version 0.1.0
    * [x] Implement all GET calls
    * [x] Usable error handling
    * [x] Network stuff
    * [x] Comprehensive example
 * Version 0.2.0
     * [x] Escape user input
     * [x] Implement all PATCH calls
     * [x] Implement all POST calls
     * [ ] Implement all DELETE calls
 * Version 0.3.0
    * [ ] Handle HTTP statuses 301 & 302
    * [ ] Support registering as an application
 * Later
    * [ ] Asynchronous I/O
    * [ ] Handle X-RateLimit header
    * [ ] Find out why the "short read" error occurs with PATCH and POST

## Status of implementation

 * [x] GET /api/v1/accounts/:id
 * [x] GET /api/v1/accounts/verify_credentials
 * [x] PATCH /api/v1/accounts/update_credentials
 * [x] GET /api/v1/accounts/:id/followers
 * [x] GET /api/v1/accounts/:id/following
 * [x] GET /api/v1/accounts/:id/statuses
 * [x] POST /api/v1/accounts/:id/follow
 * [x] POST /api/v1/accounts/:id/unfollow
 * [x] POST /api/v1/accounts/:id/block
 * [x] POST /api/v1/accounts/:id/unblock
 * [x] POST /api/v1/accounts/:id/mute
 * [x] POST /api/v1/accounts/:id/unmute
 * [x] GET /api/v1/accounts/relationships
 * [x] GET /api/v1/accounts/search
 * [x] POST /api/v1/apps
 * [x] GET /api/v1/blocks
 * [x] GET /api/v1/domain_blocks
 * [x] POST /api/v1/domain_blocks
 * [ ] DELETE /api/v1/domain_blocks
 * [x] GET /api/v1/favourites
 * [x] GET /api/v1/follow_requests
 * [x] POST /api/v1/follow_requests/:id/authorize
 * [x] POST /api/v1/follow_requests/:id/reject
 * [x] POST /api/v1/follows
 * [x] GET /api/v1/instance
 * [x] GET /api/v1/custom_emojis
 * [x] GET /api/v1/lists
 * [x] GET /api/v1/accounts/:id/lists
 * [x] GET /api/v1/lists/:id/accounts
 * [x] GET /api/v1/lists/:id
 * [x] POST /api/v1/lists
 * [ ] PUT /api/v1/lists/:id
 * [ ] DELETE /api/v1/lists/:id
 * [x] POST /api/v1/lists/:id/accounts
 * [ ] DELETE /api/v1/lists/:id/accounts
 * [x] POST /api/v1/media
 * [x] GET /api/v1/mutes
 * [x] GET /api/v1/notifications
 * [x] GET /api/v1/notifications/:id
 * [x] POST /api/v1/notifications/clear
 * [x] POST /api/v1/notifications/dismiss
 * [x] GET /api/v1/reports
 * [x] POST /api/v1/reports
 * [x] GET /api/v1/search
 * [x] GET /api/v1/statuses/:id
 * [x] GET /api/v1/statuses/:id/context
 * [x] GET /api/v1/statuses/:id/card
 * [x] GET /api/v1/statuses/:id/reblogged_by
 * [x] GET /api/v1/statuses/:id/favourited_by
 * [x] POST /api/v1/statuses
 * [ ] DELETE /api/v1/statuses/:id
 * [x] POST /api/v1/statuses/:id/reblog
 * [x] POST /api/v1/statuses/:id/unreblog
 * [x] POST /api/v1/statuses/:id/favourite
 * [x] POST /api/v1/statuses/:id/unfavourite
 * [x] POST /api/v1/statuses/:id/pin
 * [x] POST /api/v1/statuses/:id/unpin
 * [x] POST /api/v1/statuses/:id/mute
 * [x] POST /api/v1/statuses/:id/unmute
 * [x] GET /api/v1/timelines/home
 * [x] GET /api/v1/timelines/public
 * [x] GET /api/v1/timelines/tag/:hashtag
 * [x] GET /api/v1/timelines/list/:list_id

[Full reference](https://github.com/tootsuite/documentation/blob/master/Using-the-API/API.md)

# Copyright

    Copyright © 2018 tastytea <tastytea@tastytea.de>.
    License GPLv3: GNU GPL version 3 <https://www.gnu.org/licenses/gpl-3.0.html>.
    This program comes with ABSOLUTELY NO WARRANTY. This is free software,
    and you are welcome to redistribute it under certain conditions.
