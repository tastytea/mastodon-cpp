**mastodon-cpp** is a C++ wrapper for the Mastodon API.
The library takes care of the network stuff. You submit a query and get the raw JSON.

# Install

## Packages

Every [release](https://github.com/tastytea/mastodon-cpp/releases) includes
packages for the package managers of Gentoo, Debian and Red Hat.

### Gentoo

Put the ebuild into your [local overlay](https://wiki.gentoo.org/wiki/Custom_repository) and run ebuild \<ebuild path\> manifest.
Install with `emerge mastodon-cpp`.

### DEB and RPM

Prebuilt DEB and RPM packages for x86_64(amd64) are provided with each release.
These packages are automatically built and not tested.
Install with `dpkg -i` or `rpm -i`, respectively.

To use the DEB package on stretch, you will need [libcurlpp0](https://packages.debian.org/de/libcurlpp0) from buster or jessie.

## From source

### Dependencies

* Tested OS: GNU/Linux
* C++ compiler (tested: gcc 6.4/5.4, clang 5.0)
* [cmake](https://cmake.org/) (tested: 3.9.6)
* [libcurl](https://curl.haxx.se/) (tested: 7.58.0/7.35.0)
* [curlpp](http://www.curlpp.org/) (tested: 0.8.1/0.7.3)
* Optional
    * Documentation: [doxygen](https://www.stack.nl/~dimitri/doxygen/) (tested: 1.8.13)
    * Examples: [boost](http://www.boost.org/) (tested: 1.63.0/1.54.0)
    * DEB package: [dpkg](https://packages.qa.debian.org/dpkg) (tested: 1.19.0.5)
    * RPM package: [rpm](http://www.rpm.org) (tested: 4.11.0.1)

### Get sourcecode

#### Release

Download the current release at [GitHub](https://github.com/tastytea/mastodon-cpp/releases).

#### Development version

[![Build Status](https://travis-ci.org/tastytea/mastodon-cpp.svg?branch=master)](https://travis-ci.org/tastytea/mastodon-cpp)

    git clone https://github.com/tastytea/mastodon-cpp.git

### Compile

    mkdir build
    cd build/
    cmake ..
    make

cmake options:

 * `-DCMAKE_BUILD_TYPE=Debug` for a debug build
 * `-DWITH_EXAMPLES=ON` if you want to compile the examples
 * `-DWITH_TESTS=ON` if you want to compile the tests
 * `-DWITH_DOC=ON` if you want to compile the HTML reference
 * `-DWITH_DEB=ON` if you want to be able to generate a deb-package
 * `-DWITH_RPM=ON` if you want to be able to generate an rpm-package

You can run the tests with `ctest ..` inside the build directory.
To install, run `make install`

### Packages

#### Gentoo

Put the ebuild in `packages/gentoo` into your [local overlay](https://wiki.gentoo.org/wiki/Custom_repository) and rename it to match the desired version or use the live-ebuild (mastodon-cpp-9999.ebuild) to install the development version.

#### DEB and RPM

Compile with `-DWITH_DEB=ON` or `-DWITH_RPM=ON`.
Run `make package` from the build directory to generate a DEB/RPM package.

#### Other

Run `make package` from the build directory to generate a tar.gz archive.

# Usage

The HTML reference can be generated with `build_doc.sh`, if doxygen is installed.
Or just look in `src/mastodon-cpp.hpp`. It is also available at [tastytea.github.io/mastodon-cpp/](https://tastytea.github.io/mastodon-cpp/docs/classMastodon_1_1API.html).
There are examples in `src/examples/`.

## Most basic example

    #include <iostream>
    #include <string>
    #include <mastodon-cpp.hpp>

    int main()
    {
        Mastodon::API masto("social.example.com", "auth_token");
        std::string answer;
        masto.get(Mastodon::API::v1::accounts_verify_credentials, answer);
        std::cout << answer << '\n';
    }

## Compiling your project

After you did a `make install`, a project consisting of one file can be compiled as follows:

    g++ -std=c++14 -lmastodon-cpp example.cpp

## Error codes

mastodon-cpp will never use error codes below 11, except 0.

|      Code | Explanation                   |
| --------: |:------------------------------|
|         0 | No error                      |
|        11 | Invalid call                  |
|        12 | Not implemented               |
|        13 | URL changed (HTTP 301 or 308) |
|        14 | Aborted by user               |
|        20 | Failed to connect             |
|        21 | Couldn't resolve host         |
|        22 | Network is unreachable        |
| 100 - 999 | HTTP status codes             |
|     65535 | Unknown error                 |

If you use a debug build, you get more verbose error messages.

## Useful links

* [Mastodon API reference](https://github.com/tootsuite/documentation/blob/master/Using-the-API/API.md)
* [Mastodon streaming API reference](https://github.com/tootsuite/documentation/blob/master/Using-the-API/Streaming-API.md)

# Status of implementation

Feature complete as of Mastodon 2.2.0

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
 * [x] DELETE /api/v1/domain_blocks
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
 * [x] PUT /api/v1/lists/:id
 * [x] DELETE /api/v1/lists/:id
 * [x] POST /api/v1/lists/:id/accounts
 * [x] DELETE /api/v1/lists/:id/accounts
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
 * [x] DELETE /api/v1/statuses/:id
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
 * [x] GET /api/v1/streaming/user
 * [x] GET /api/v1/streaming/public
 * [x] GET /api/v1/streaming/public/local
 * [x] GET /api/v1/streaming/hashtag
 * [x] GET /api/v1/streaming/list

# Copyright

    Copyright © 2018 tastytea <tastytea@tastytea.de>.
    License GPLv3: GNU GPL version 3 <https://www.gnu.org/licenses/gpl-3.0.html>.
    This program comes with ABSOLUTELY NO WARRANTY. This is free software,
    and you are welcome to redistribute it under certain conditions.
