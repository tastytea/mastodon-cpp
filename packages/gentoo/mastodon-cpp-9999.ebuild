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
IUSE="doc debug examples"
RDEPEND=">=dev-cpp/curlpp-0.8.1"
DEPEND=">=dev-util/cmake-3.9.6
        doc? ( >=app-doc/doxygen-1.8.13-r1 )
        examples? ( >=dev-libs/boost-1.63.0 )
        ${RDEPEND}"

src_unpack() {
    git-r3_src_unpack
}

src_configure() {
    local mycmakeargs=(
        -DWITH_DOC=NO
        -DWITH_EXAMPLES=NO
        -DWITH_TESTS=NO
    )
    if use debug; then
        mycmakeargs+=(-DCMAKE_BUILD_TYPE=Debug)
    else
        mycmakeargs+=(-DCMAKE_BUILD_TYPE=Release)
    fi
    cmake-utils_src_configure
}

# We can not let cmake handle the documentation, because it would end up in
# doc/mastodon-cpp-${PROJECT_VERSION} instead of -9999
src_compile() {
    if use doc; then
        ./build_doc.sh
    fi
    cmake-utils_src_compile
}

src_install() {
    if use doc; then
        HTML_DOCS="doc/html/*"
    fi

    if use examples; then
        docinto examples
        for file in src/examples/*.cpp; do
            dodoc ${file}
        done
    fi
    
    cmake-utils_src_install
}
