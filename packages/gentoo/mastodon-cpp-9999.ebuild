# Copyright 1999-2017 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Id$

EAPI=6
inherit git-r3 cmake-utils

DESCRIPTION="mastodon-cpp is a C++ wrapper for the Mastodon API."
HOMEPAGE="https://git.schlomp.space/tastytea/mastodon-cpp"
EGIT_REPO_URI="https://git.schlomp.space/tastytea/mastodon-cpp.git"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS=""
IUSE="doc debug examples"
RDEPEND=">=dev-cpp/curlpp-0.8.1
		>=dev-libs/jsoncpp-1.8.4"
DEPEND=">=dev-util/cmake-3.9.6
		doc? ( >=app-doc/doxygen-1.8.14-r1 )
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
	cmake-utils_src_compile

	if use doc; then
		./build_doc.sh
	fi
}

src_install() {
	if use doc; then
		HTML_DOCS="doc/html/*"
	fi

	if use examples; then
		docinto examples
		for file in examples/*.cpp; do
			dodoc ${file}
		done
	fi
	
	cmake-utils_src_install
}
