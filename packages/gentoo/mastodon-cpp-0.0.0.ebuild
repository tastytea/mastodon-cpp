# Copyright 1999-2018 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2

EAPI=6
inherit cmake-utils

DESCRIPTION="mastodon-cpp is a C++ wrapper for the Mastodon API."
HOMEPAGE="https://schlomp.space/tastytea/mastodon-cpp"
SRC_URI="https://schlomp.space/tastytea/mastodon-cpp/archive/${PV}.tar.gz -> ${P}.tar.gz"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS="~amd64"
IUSE="doc debug examples static-libs"
RDEPEND=">=dev-cpp/curlpp-0.8.1
		 >=dev-libs/jsoncpp-1.8.4"
DEPEND=">=dev-util/cmake-3.9.6
		doc? ( >=app-doc/doxygen-1.8.14-r1 )
		${RDEPEND}"

src_unpack() {
	default_src_unpack

	mv ${PN} ${P}
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
	if use static-libs; then
		mycmakeargs+=(-DWITH_STATIC=YES)
	fi

	cmake-utils_src_configure
}

# We won't let cmake handle the documentation, because it would install the
# examples, no matter if we want them.
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
