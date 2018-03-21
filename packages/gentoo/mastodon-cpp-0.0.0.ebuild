EAPI=6
inherit cmake-utils

DESCRIPTION="mastodon-cpp is a C++ wrapper for the Mastodon API."
HOMEPAGE="https://github.com/tastytea/mastodon-cpp"
SRC_URI="https://github.com/tastytea/mastodon-cpp/archive/${PV}.tar.gz -> ${P}.tar.gz"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS=""
IUSE="doc debug examples"
RDEPEND=">=dev-cpp/curlpp-0.7.3
         >=dev-libs/jsoncpp-1.8.1"
DEPEND=">=dev-util/cmake-3.9.6
        doc? ( >=app-doc/doxygen-1.8.13-r1 )
        ${RDEPEND}"

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

# We won't let cmake handle the documentation, because it would install the
# examples, no matter if we want them.
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
        for file in examples/*.cpp; do
            dodoc ${file}
        done
    fi
    
    cmake-utils_src_install
}
