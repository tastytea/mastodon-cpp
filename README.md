**mastodon-cpp** is a C++ wrapper for the Mastodon API.
The library takes care of the network stuff. You submit a query and get the raw
JSON. You can then put that JSON into easy to use classes.

[TODO-list](https://schlomp.space/tastytea/mastodon-cpp/milestones)

**The ABI will be unstable in versions < 1.0.0**

**Beginning with 0.30.0, all IDs are `const string` instead of
`uint_fast64_t` as required by the Mastodon API. Sorry for the inconvenience.**

# Breaking API changes

I'm going to rewrite key parts of this library. The new API will be incompatible
with the old one. The new code will start with the version number `0.100.0`. The
old code is archived in the branch `pre-0.100.0` and will get bugfixes for a
while.

**The code on the `master`-branch is not usable at the moment, stick to the
releases, please.**

# Usage

The HTML reference can be generated with `build_doc.sh`, if doxygen is installed. It is also available at
[doc.schlomp.space/mastodon-cpp/](https://doc.schlomp.space/mastodon-cpp/annotated.html).
There are [examples](https://schlomp.space/tastytea/mastodon-cpp/src/branch/master/examples) in `examples/`.

## Most basic example

```C++
#include <iostream>
#include <string>
#include <mastodon-cpp/mastodon-cpp.hpp>

int main()
{
    Mastodon::API masto("social.example.com", "auth_token");
    std::string answer;
    masto.get(Mastodon::API::v1::accounts_verify_credentials, answer);
    std::cout << answer << '\n';
}
```

## Another simple example

Using the `Easy`-class.

```C++
#include <iostream>
#include <string>
#include <vector>
#include <mastodon-cpp/mastodon-cpp.hpp>
#include <mastodon-cpp/easy/all.hpp>

using Mastodon::Easy;

int main()
{
    Easy masto("social.example", "");
    std::string answer;
    masto.get(Mastodon::API::v1::timelines_public, answer);

    for (const std::string &str : Easy::json_array_to_vector(answer))
    {
        Easy::Status status(str);
        std::cout << "  " << status.account().acct() << " wrote:\n";
        std::cout << status.content() << '\n';
    }
}
```

## Compiling your project

A project consisting of one file can be compiled as follows:

```SH
g++ -std=c++14 -lmastodon-cpp example.cpp
```

## Error codes

|      Code | Explanation                                |
| --------: |:-------------------------------------------|
|         0 | No error                                   |
|        22 | Invalid argument                           |
|        78 | URL changed (HTTP 301 or 308)              |
|       110 | Connection timed out                       |
|       111 | Connection refused (check http_error_code) |
|       192 | curlpp runtime error                       |
|       193 | curlpp logic error                         |
|       255 | Unknown error                              |

If you use a debug build, you get more verbose error messages.

## Useful links

* [Mastodon documentation](https://docs.joinmastodon.org/)

# Install

## Packages

Every [release](https://schlomp.space/tastytea/mastodon-cpp/releases) includes
packages for the package managers of Debian and Red Hat. Gentoo packages are
available in an overlay.

### Gentoo

Add my [repository](https://schlomp.space/tastytea/overlay) and
install it from there.

```SH
eselect repository enable tastytea
echo 'dev-cpp/mastodon-cpp ~amd64' >> /etc/portage/package.keywords/mastodon-cpp
emaint sync -r tastytea
emerge -a dev-cpp/mastodon-cpp
```

### DEB and RPM

Prebuilt DEB and RPM packages for x86_64(amd64) are provided with each release.
These packages are automatically built and not tested.
Install with `dpkg -i` or `rpm -i`, respectively.

To use the DEB package on stretch, you will need [libcurlpp0](https://packages.debian.org/libcurlpp0) from sid.

## From source

### Dependencies

* Tested OS: Linux
* C++ compiler (tested: gcc 5 / 6 / 7 / 8)
* [cmake](https://cmake.org/) (tested: 3.9 / 3.12)
* [pkgconfig](https://pkgconfig.freedesktop.org/wiki/) (tested: 0.29)
* [curlpp](http://www.curlpp.org/) (tested: 0.8)
* Optional
    * Easy interface & Examples: [jsoncpp](https://github.com/open-source-parsers/jsoncpp) (tested: 1.8 / 1.7)
    * Documentation: [doxygen](https://www.stack.nl/~dimitri/doxygen/) (tested: 1.8)
    * DEB package: [dpkg](https://packages.qa.debian.org/dpkg) (tested: 1.19 / 1.18)
    * RPM package: [rpm](http://www.rpm.org) (tested: 4.14 / 4.12)

### Get sourcecode

#### Release

Download the current release at [schlomp.space](https://schlomp.space/tastytea/mastodon-cpp/releases).

#### Development version

```SH
git clone https://schlomp.space/tastytea/mastodon-cpp.git
```

### Compile

```SH
mkdir build
cd build/
cmake ..
make
```

cmake options:

 * `-DCMAKE_BUILD_TYPE=Debug` for a debug build
 * `-DWITHOUT_EASY=ON` to not build the Easy abstractions and to get rid of the jsoncpp-dependency (not recommended)
 * `-DWITH_EXAMPLES=ON` if you want to compile the examples
 * `-DWITH_TESTS=ON` if you want to compile the tests
 * `-DWITH_STATIC=ON` If you want a static library along with the dynamic one
 * `-DWITH_DOC=ON` if you want to compile the HTML reference
 * `-DWITH_DEB=ON` if you want to be able to generate a deb-package
 * `-DWITH_RPM=ON` if you want to be able to generate an rpm-package

You can run the tests with `ctest ..` inside the build directory.
To install, run `make install`.

### Packages

#### DEB and RPM

Compile with `-DWITH_DEB=ON` or `-DWITH_RPM=ON`.
Run `make package` from the build directory to generate a DEB/RPM package.

#### Other

Run `make package` from the build directory to generate a tar.gz archive.

# Status of implementation

Feature complete as of Mastodon 2.6.1

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
 * [x] GET /api/v1/endorsements
 * [x] POST /api/v1/accounts/:id/pin
 * [x] POST /api/v1/accounts/:id/unpin
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
 * [x] PUT /api/v1/media/:id
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
 * [x] POST /api/v1/push/subscription
 * [x] GET /api/v1/push/subscription
 * [x] PUT /api/v1/push/subscription
 * [x] DELETE /api/v1/push/subscription
 * [x] GET /api/v2/search

## Glitch-Soc support

* [x] max_toot_chars in /api/v1/instance
* [x] GET /api/v1/bookmarks
* [x] POST /api/v1/statuses/:id/bookmark
* [x] POST /api/v1/statuses/:id/unbookmark

# Copyright

```PLAIN
Copyright © 2018 tastytea <tastytea@tastytea.de>.
License GPLv3: GNU GPL version 3 <https://www.gnu.org/licenses/gpl-3.0.html>.
This program comes with ABSOLUTELY NO WARRANTY. This is free software,
and you are welcome to redistribute it under certain conditions.
```
