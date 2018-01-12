**mastodon-cpp** is a CPP wrapper for the Mastodon API. The aim is to be as simple as possible.
The library takes care of the network stuff. You submit a query and get the raw JSON.
All versions below 1.0.0 (SOVERSION 0) are considered insecure, unstable and can change drastically any time.

# Install
## Dependencies
 * Tested OS: Linux
 * C++ compiler (tested: gcc 6.4)
 * [cmake](https://cmake.org/) (tested: 3.9.6)
 * [boost](http://www.boost.org/) (tested: 1.63.0)

## Get sourcecode
### Development version
    git clone https://…

## Compile
    mkdir build
    cd build/
    cmake ..
    make

# Usage
    Mastodon::API masto("social.example.com", "access token");
    std::cout << masto.get(Mastodon::API::v1::timelines_home) << '\n';
    std::cout << masto.get(Mastodon::API::v1::accounts_id, "12345") << '\n';

There is an example in `src/example`.

# TODO
 * Version 0.1.0
    * [ ] Implement all GET methods
    * [ ] Proper error handling
    * [x] Network stuff
    * [ ] Comprehensive example
 * Version 0.2.0
     * [ ] Implement all PATCH methods
     * [ ] Implement all POST methods
     * [ ] Implement all DELETE methods
 * Later
    [ ] Escape user input
    [ ] Asynchronous I/O

## Status of implementation
 * [x] GET /api/v1/accounts/:id
 * [x] GET /api/v1/accounts/verify_credentials
 * [ ] PATCH /api/v1/accounts/update_credentials
 * [x] GET /api/v1/accounts/:id/followers
 * [x] GET /api/v1/accounts/:id/following
 * [x] GET /api/v1/accounts/:id/statuses
 * [ ] POST /api/v1/accounts/:id/follow
 * [ ] POST /api/v1/accounts/:id/unfollow
 * [ ] POST /api/v1/accounts/:id/block
 * [ ] POST /api/v1/accounts/:id/unblock
 * [ ] POST /api/v1/accounts/:id/mute
 * [ ] POST /api/v1/accounts/:id/unmute
 * [x] GET /api/v1/accounts/relationships
 * [x] GET /api/v1/accounts/search
 * [ ] POST /api/v1/apps
 * [x] GET /api/v1/blocks
 * [x] GET /api/v1/domain_blocks
 * [ ] POST /api/v1/domain_blocks
 * [ ] DELETE /api/v1/domain_blocks
 * [x] GET /api/v1/favourites
 * [x] GET /api/v1/follow_requests
 * [ ] POST /api/v1/follow_requests/:id/authorize
 * [ ] POST /api/v1/follow_requests/:id/reject
 * [ ] POST /api/v1/follows
 * [x] GET /api/v1/instance
 * [x] GET /api/v1/custom_emojis
 * [x] GET /api/v1/lists
 * [x] GET /api/v1/accounts/:id/lists
 * [x] GET /api/v1/lists/:id/accounts
 * [x] GET /api/v1/lists/:id
 * [ ] POST /api/v1/lists
 * [ ] PUT /api/v1/lists/:id
 * [ ] DELETE /api/v1/lists/:id
 * [ ] POST /api/v1/lists/:id/accounts
 * [ ] DELETE /api/v1/lists/:id/accounts
 * [ ] POST /api/v1/media
 * [x] GET /api/v1/mutes
 * [x] GET /api/v1/notifications
 * [x] GET /api/v1/notifications/:id
 * [ ] POST /api/v1/notifications/clear
 * [ ] POST /api/v1/notifications/dismiss
 * [x] GET /api/v1/reports
 * [ ] POST /api/v1/reports
 * [x] GET /api/v1/search
 * [x] GET /api/v1/statuses/:id
 * [x] GET /api/v1/statuses/:id/context
 * [x] GET /api/v1/statuses/:id/card
 * [x] GET /api/v1/statuses/:id/reblogged_by
 * [x] GET /api/v1/statuses/:id/favourited_by
 * [ ] POST /api/v1/statuses
 * [ ] DELETE /api/v1/statuses/:id
 * [ ] POST /api/v1/statuses/:id/reblog
 * [ ] POST /api/v1/statuses/:id/unreblog
 * [ ] POST /api/v1/statuses/:id/favourite
 * [ ] POST /api/v1/statuses/:id/unfavourite
 * [ ] POST /api/v1/statuses/:id/pin
 * [ ] POST /api/v1/statuses/:id/unpin
 * [ ] POST /api/v1/statuses/:id/mute
 * [ ] POST /api/v1/statuses/:id/unmute
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
