**mastodon-cpp** is a C++ wrapper for the Mastodon API. You submit an API call
and get the raw JSON or easy to use abstractions.

**The ABI will be unstable in versions < 1.0.0**

[Subscribe to mastodon-cpp releases](https://rss.schlomp.space/?repo=tastytea/mastodon-cpp).

# Usage

The HTML reference can be generated with `build_doc.sh`, if doxygen is
installed. It is also available at
[doc.schlomp.space/mastodon-cpp/](https://doc.schlomp.space/mastodon-cpp/annotated.html).
There are [examples](https://schlomp.space/tastytea/mastodon-cpp/src/branch/master/examples)
in `examples/`.

## Most basic example

```c++
#include <iostream>
#include <mastodon-cpp/mastodon-cpp.hpp>

int main()
{
    Mastodon::API masto("social.example.com", "auth_token");
    std::cout << masto.get(Mastodon::API::v1::accounts_verify_credentials);
    std::cout << std::endl;
}
```

## Another simple example

Using the `Easy` interface.

```c++
#include <iostream>
#include <string>
#include <mastodon-cpp/mastodon-cpp.hpp>
#include <mastodon-cpp/easy/all.hpp>

using Mastodon;

int main()
{
    Easy::API masto("social.example", "");
    return_call ret = masto.get(API::v1::timelines_public);

    for (const std::string &str : Easy::json_array_to_vector(ret.answer))
    {
        Easy::Status status(str);
        std::cout << "  " << status.account().acct() << " wrote:\n";
        std::cout << status.content() << '\n';
    }
}
```

## Compiling your project

A project consisting of one file can be compiled as follows:

``` shellsession
g++ -std=c++14 -lmastodon-cpp example.cpp
```

## List of types

Learn more at <https://doc.schlomp.space/mastodon-cpp/namespaceMastodon.html>
and <https://doc.schlomp.space/mastodon-cpp/namespaceMastodon_1_1Easy.html>.

### Return types

* `Mastodon::return_call`: Contains the response from `Mastodon::API` calls.
* `Mastodon::Easy::return_entity`: Contains the response from
  `Mastodon::Easy::API` calls that return a single `Mastodon::Easy::Entity`.
* `Mastodon::Easy::return_entities_vector`: Contains the response from
  `Mastodon::Easy::API` calls that return multiple `Mastodon::Easy::Entity`.

### Other types

* `Mastodon::param`: A single parameter to an `Mastodon::API` call. Normally you
  don't need this.
* `Mastodon::parameters`: All parameters to an `Mastodon::API` call.
* `Mastodon::http_method`: HTTP method of an `Mastodon::API` call.
* `Mastodon::Easy::event_type`: Event types returned in streams.
* `Mastodon::Easy::visibility_type`: Describes the visibility of a post.
* `Mastodon::Easy::attachment_type`: Describes the type of attachment.
* `Mastodon::Easy::card_type`: Describes the type of card.
* `Mastodon::Easy::notification_type`: The type of the notification.
* `Mastodon::Easy::stream_event`: Type and data of an events returned in
  streams.
* `Mastodon::Easy::alert_type`: Type for a single alert.
* `Mastodon::Easy::alerts`: Vector of `Mastodon::Easy::alert_type`, used for
  push subscriptions.
* `Mastodon::Easy::time`: Type for time, can be converted to `time_point` and
  `string`.

## Error codes

|      Code | Explanation                                |
| --------: |:-------------------------------------------|
|         0 | No error                                   |
|        22 | Invalid argument                           |
|        78 | URL changed (HTTP 301 or 308)              |
|       110 | Connection timed out                       |
|       111 | Connection refused (check http_error_code) |
|       113 | No route to host / Could not resolve host  |
|       192 | curlpp runtime error                       |
|       193 | curlpp logic error                         |
|       255 | Unknown error                              |

If you use a debug build, you get more verbose error messages.

## Useful links

* [Mastodon documentation](https://docs.joinmastodon.org/)
* [Pleroma documentation](https://git.pleroma.social/pleroma/pleroma/tree/develop/docs/api)
* [glitch-soc documentation](https://glitch-soc.github.io/docs/#whats-different)

# Install

## Upgrading from versions below 0.100.0

Starting with version `0.100.0`, large parts of the library have been rewritten.
Upgrading from previous versions will require extensive code changes. You can
keep using the old version, it is archived in the branch
[pre-0.100.0](https://schlomp.space/tastytea/mastodon-cpp/src/branch/pre-0.100.0).
It will receive bug-fixes for a while but no new features.

## Packages

Every [release](https://schlomp.space/tastytea/mastodon-cpp/releases) includes
packages for the package managers of Debian and Red Hat. Gentoo packages are
available in my overlay.

### Gentoo

Add my [repository](https://schlomp.space/tastytea/overlay) and
install it from there.

```shellsession
eselect repository enable tastytea
echo 'dev-cpp/mastodon-cpp ~amd64' >> /etc/portage/package.accept_keywords/mastodon-cpp
emaint sync -r tastytea
emerge -a dev-cpp/mastodon-cpp
```

### DEB and RPM

Prebuilt DEB and RPM packages for x86_64(amd64) are provided with each release.
`.deb` packages are built on Debian stretch and `.rpm` packages are built on
CentOS 7. These packages are automatically built and not tested.

To use the DEB`.deb` package on Debian stretch, you will need
[libcurlpp0](https://packages.debian.org/libcurlpp0) from sid.

To use the `.rpm` package on CentOS 7, you will need
[libcurlpp](https://download.fedoraproject.org/pub/epel/6/x86_64/Packages/c/)
from EPEL 6.

## From source

### Dependencies

* Tested OS: Linux
* C++ compiler (tested: [gcc](https://gcc.gnu.org/) 6/7/8,
  [clang](https://llvm.org/) 5/6)
* [cmake](https://cmake.org/) (at least: 3.6)
* [pkgconfig](https://pkgconfig.freedesktop.org/wiki/) (tested: 0.29 / 0.27)
* [curlpp](http://www.curlpp.org/) (tested: 0.8)
* Optional
    * Easy interface & Examples: [jsoncpp](https://github.com/open-source-parsers/jsoncpp) (tested: 1.8 / 1.7)
    * Documentation: [doxygen](https://www.stack.nl/~dimitri/doxygen/) (tested: 1.8)
    * DEB package: [dpkg](https://packages.qa.debian.org/dpkg) (tested: 1.18)
    * RPM package: [rpm-build](http://www.rpm.org) (tested: 4.11)
    * Tests: [catch](https://github.com/catchorg/Catch2) (tested: 2.5 / 1.2)

### Get sourcecode

#### Release

Download the current release at
[schlomp.space](https://schlomp.space/tastytea/mastodon-cpp/releases).

#### Development version

```shellsession
git clone https://schlomp.space/tastytea/mastodon-cpp.git
```

### Compile

```shellsession
mkdir build
cd build/
cmake ..
cmake --build . -- -j$(nproc --ignore=1)
```

cmake options:

 * `-DCMAKE_BUILD_TYPE=Debug` for a debug build
 * `-DWITH_EASY=NO` to not build the Easy abstractions and to get rid of the
   jsoncpp-dependency (not recommended)
 * `-DWITH_EXAMPLES=YES` if you want to compile the examples
 * `-DWITH_TESTS=YES` if you want to compile the tests
 * `-DEXTRA_TEST_ARGS` to run only some tests
   * Possible values: `[api]`, `[mastodon]`, `[glitch-soc]`, `[pleroma]`
 * `-DWITH_DOC=NO` if you don't want to compile the HTML reference
 * One of:
    * `-DWITH_DEB=YES` if you want to be able to generate a deb-package
    * `-DWITH_RPM=YES` if you want to be able to generate an rpm-package

Install with `make install`.

### Tests

You can run the tests with `ctest` inside the build directory. You need to set
the environment variable `MASTODON_CPP_ACCESS_TOKEN` to an access token with the
scopes *read*, *write* and *follow* for some tests.
You can select the instance to use with `MASTODON_CPP_INSTANCE`, the default is
*likeable.space*. You can select the user ID with `MASTODON_CPP_USER_ID`, the
default is *9hnrrVPriLiLVAhfVo*. You can select the status ID with
`MASTODON_CPP_STATUS_ID`, the default is *9hwnuJMq3eTdO4s1PU*. You can select
the filter ID with `MASTODON_CPP_FILTER_ID`.

Requirements for the test-user:

* Have at least 1 follower.
* Follow at least 1 account.
* Have at least 1 account endorsed.
* Have at least 1 public or unlisted status.
* Have at least 1 post favourited.

### Packages

#### DEB and RPM

Compile with `-DWITH_DEB=ON` or `-DWITH_RPM=ON`.
Run `make package` from the build directory to generate a DEB/RPM package.

#### Other

Run `make package` from the build directory to generate a tar.gz archive.

# Status of implementation

~~Feature complete as of Mastodon 2.6.1~~

 * [x] GET /api/v1/accounts/:id
 * [x] POST /api/v1/accounts
 * [x] GET /api/v1/accounts/verify_credentials
 * [x] PATCH /api/v1/accounts/update_credentials
 * [x] GET /api/v1/accounts/:id/followers
 * [x] GET /api/v1/accounts/:id/following
 * [x] GET /api/v1/accounts/:id/statuses
 * [x] POST /api/v1/accounts/:id/follow
 * [x] POST /api/v1/accounts/:id/unfollow
 * [x] GET /api/v1/accounts/relationships
 * [x] GET /api/v1/accounts/search
 * [x] POST /api/v1/apps
 * [x] GET /api/v1/apps/verify_credentials
 * [x] GET /api/v1/blocks
 * [x] POST /api/v1/accounts/:id/block
 * [x] POST /api/v1/accounts/:id/unblock
 * [x] GET /api/v1/custom_emojis
 * [x] GET /api/v1/domain_blocks
 * [x] POST /api/v1/domain_blocks
 * [x] DELETE /api/v1/domain_blocks
 * [x] GET /api/v1/endorsements
 * [x] POST /api/v1/accounts/:id/pin
 * [x] POST /api/v1/accounts/:id/unpin
 * [x] GET /api/v1/favourites
 * [x] POST /api/v1/statuses/:id/favourite
 * [x] POST /api/v1/statuses/:id/unfavourite
 * [x] GET /api/v1/filters
 * [x] POST /api/v1/filters
 * [x] GET /api/v1/filters/:id
 * [x] PUT /api/v1/filters/:id
 * [x] DELETE /api/v1/filters/:id
 * [x] GET /api/v1/follow_requests
 * [x] POST /api/v1/follow_requests/:id/authorize
 * [x] POST /api/v1/follow_requests/:id/reject
 * [ ] GET /api/v1/suggestions
 * [ ] DELETE /api/v1/suggestions/:account_id
 * [x] GET /api/v1/instance
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
 * [x] POST /api/v1/accounts/:id/mute
 * [x] POST /api/v1/accounts/:id/unmute
 * [x] POST /api/v1/statuses/:id/mute
 * [x] POST /api/v1/statuses/:id/unmute
 * [x] GET /api/v1/notifications
 * [x] GET /api/v1/notifications/:id
 * [x] POST /api/v1/notifications/clear
 * [x] POST /api/v1/notifications/dismiss
 * [x] POST /api/v1/push/subscription
 * [x] GET /api/v1/push/subscription
 * [x] PUT /api/v1/push/subscription
 * [x] DELETE /api/v1/push/subscription
 * [x] ~~GET /api/v1/reports~~ (Deprecated)
 * [x] POST /api/v1/reports
 * [ ] GET /api/v1/scheduled_statuses
 * [ ] GET /api/v1/scheduled_statuses/:id
 * [ ] PUT /api/v1/scheduled_statuses/:id
 * [ ] DELETE /api/v1/scheduled_statuses/:id
 * [x] ~~GET /api/v1/search~~ (Deprecated)
 * [x] GET /api/v2/search
 * [x] GET /api/v1/statuses/:id
 * [x] GET /api/v1/statuses/:id/context
 * [x] GET /api/v1/statuses/:id/card
 * [x] GET /api/v1/statuses/:id/reblogged_by
 * [x] GET /api/v1/statuses/:id/favourited_by
 * [x] POST /api/v1/statuses
 * [x] DELETE /api/v1/statuses/:id
 * [x] POST /api/v1/statuses/:id/reblog
 * [x] POST /api/v1/statuses/:id/unreblog
 * [x] POST /api/v1/statuses/:id/pin
 * [x] POST /api/v1/statuses/:id/unpin
 * [x] GET /api/v1/timelines/home
 * [ ] GET /api/v1/conversations
 * [x] GET /api/v1/timelines/public
 * [x] GET /api/v1/timelines/tag/:hashtag
 * [x] GET /api/v1/timelines/list/:list_id
 * [x] GET /api/v1/streaming/user
 * [x] GET /api/v1/streaming/public
 * [x] GET /api/v1/streaming/public/local
 * [x] GET /api/v1/streaming/hashtag
 * [ ] GET /api/v1/streaming/hashtag/local
 * [x] GET /api/v1/streaming/list
 * [ ] GET /api/v1/streaming/direct

## Glitch-Soc support

* [x] max_toot_chars in /api/v1/instance
* [x] GET /api/v1/bookmarks
* [x] POST /api/v1/statuses/:id/bookmark
* [x] POST /api/v1/statuses/:id/unbookmark

# Copyright

``` text
Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>.
License GPLv3: GNU GPL version 3 <https://www.gnu.org/licenses/gpl-3.0.html>.
This program comes with ABSOLUTELY NO WARRANTY. This is free software,
and you are welcome to redistribute it under certain conditions.
```
