# Copyright 1999-2017 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Id$

EAPI=6
inherit git-r3 cmake-utils

DESCRIPTION="mastodon-cpp is a C++ wrapper for the Mastodon API."
HOMEPAGE="https://github.com/tastytea/mastodon-cpp"
EGIT_REPO_URI="https://github.com/tastytea/mastodon-cpp.git"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS=""
IUSE="doc"
RDEPEND=">=dev-libs/boost-1.63.0"
DEPEND=">=dev-util/cmake-3.9.6
        doc? ( >=app-doc/doxygen-1.8.13-r1 )
        ${RDEPEND}"

src_unpack() {
    git-r3_src_unpack
}

src_configure() {
    local mycmakeargs=(
        -DWITH_DOC="$(usex doc)"
        -DWITH_EXAMPLES=NO
        -DWITH_TESTS=NO
    )
    cmake-utils_src_configure
}
