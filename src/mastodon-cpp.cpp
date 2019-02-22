/*  This file is part of mastodon-cpp.
 *  Copyright © 2018 tastytea <tastytea@tastytea.de>
 *                                                                   
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include <regex>
#include <locale>
#include <codecvt>
#include <utility>
#include "version.hpp"
#include "macros.hpp"
#include "mastodon-cpp.hpp"

#include <iostream>

using namespace Mastodon;

API::API(const string &instance, const string &access_token)
: _instance(instance)
, _access_token(access_token)
, _useragent(string("mastodon-cpp/") + global::version)
, _http(*this, instance, access_token)
, _exceptions(false)
, _proxy("")
, _proxy_userpw("")
{
    //
}

void API::set_useragent(const std::string &useragent)
{
    _useragent = useragent;
}

const string API::get_useragent() const
{
    return _useragent;
}

const string API::get_instance() const
{
    return _instance;
}

const string API::maptostr(const parametermap &map, const bool &firstparam)
{
    string result = "";
    char delim = '?';
    if (!firstparam)
    {
        delim = '&';
    }

    for (const auto &it : map)
    {
        if (it.second.size() == 1)
        {
            result += (delim + it.first + "=" + urlencode(it.second.front()));
            if (delim == '?')
            {
                delim = '&';
            }
        }
        else
        {
            for (const string &str : it.second)
            {
                result += (delim + it.first + "[]=" + urlencode(str));
                if (delim == '?')
                {
                    delim = '&';
                }
            }
        }
    }

    ttdebug << "Constructed parameter string: " << result << '\n';
    return result;
}

const curlpp::Forms API::maptoformdata(const parametermap &map)
{
    curlpp::Forms formdata;

    if (map.size() == 0)
    {
        return formdata;
    }

    for (const auto &it : map)
    {
        if (it.second.size() == 1)
        {   // If the file is not base64-encoded, treat as filename
            if ((it.first == "avatar" ||
                it.first == "header" ||
                it.first == "file") &&
                it.second.front().substr(0, 4).compare("data") != 0)
             {
                ttdebug << it.first << ": Filename detected.\n";
                formdata.push_back(
                    new curlpp::FormParts::File(it.first, it.second.front()));
             }
             else
             {
                string key = it.first;
                if (key == "account_ids" ||
                    key == "exclude_types" ||
                    key == "media_ids")
                {
                    key += "[]";
                }
                formdata.push_back(
                    new curlpp::FormParts::Content(key, it.second.front()));
            }
        }
        else
        {
            for (const string &str : it.second)
            {
                formdata.push_back(new curlpp::FormParts::Content(it.first + "[]",
                                                               str));
            }
        }
    }

    return formdata;
}

const std::string API::urlencode(const std::string &str)
{
    return curlpp::escape(str);
}

const std::string API::urldecode(const std::string &str)
{
    return curlpp::unescape(str);
}

uint16_t API::register_app1(const string &client_name,
                                 const string &redirect_uri,
                                 const string &scopes,
                                 const string &website,
                                 string &client_id,
                                 string &client_secret,
                                 string &url)
{
    API::parametermap parameters =
    {
        { "client_name", { client_name } },
        { "redirect_uris", { redirect_uri } },
        { "scopes", { scopes } },
        { "website", { website } }
    };

    string answer;
    uint16_t ret = post(API::v1::apps, parameters, answer);

    if (ret == 0)
    {
        std::smatch match;
        std::regex reid("client_id\":\"([^\"]+)\"");
        std::regex resecret("client_secret\":\"([^\"]+)\"");

        std::regex_search(answer, match, reid);
        client_id = match[1].str();
        std::regex_search(answer, match, resecret);
        client_secret = match[1].str();

        url = "https://" + _instance + "/oauth/authorize" +
              "?scope=" + urlencode(scopes) + "&response_type=code" +
              "&redirect_uri=" + urlencode(redirect_uri) +
              "&client_id=" + client_id;
        if (!website.empty())
        {
            url += "&website=" + urlencode(website);
        }

        return 0;
    }
    else if (ret == 13)
    {
        url = answer;
        return ret;
    }
    else
    {
        std::cerr << "Error code: " << ret << '\n';
        return ret;
    }
    
}

uint16_t API::register_app2(const string &client_id,
                                 const string &client_secret,
                                 const string &redirect_uri,
                                 const string &code,
                                 string &access_token)
{
    API::parametermap parameters =
    {
        { "client_id", { client_id } },
        { "client_secret", { client_secret } },
        { "grant_type", { "authorization_code" } },
        { "redirect_uri", { redirect_uri } },
        { "code", { code } },
    };

    std::string answer;
    uint16_t ret = post("/oauth/token", parameters, answer);
    if (ret == 0)
    {
        std::smatch match;
        std::regex retoken("access_token\":\"([^\"]+)\"");

        std::regex_search(answer, match, retoken);
        access_token = match[1].str();
        _access_token = access_token;

        return 0;
    }
    else
    {
        std::cerr << "Error code: " << ret << '\n';
        return ret;
    }
}

const string API::get_header(const std::string &header) const
{
    string headers;
    _http.get_headers(headers);
    size_t startpos = headers.find(header + ':');
    if (startpos != std::string::npos)
    {
        startpos = headers.find(':', startpos) + 2;
        size_t endpos = headers.find("\r\n", startpos);
        return headers.substr(startpos, endpos - startpos);
    }

    return "";
}

bool API::exceptions(const bool &value)
{
    _exceptions = value;
    return _exceptions;
}

bool API::exceptions() const
{
    return _exceptions;
}

const string API::unescape_html(const string &html)
{
    string buffer = html;
    string output = "";

    // Used to convert int to utf-8 char
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> u8c;
    // Matches numbered entities between 1 and 8 digits, decimal or hexadecimal
    std::regex re_entity("&#(x)?(\\d{1,8});");
    std::smatch match;
    
    while (std::regex_search(buffer, match, re_entity))
    {
        char32_t codepoint = 0;
        // 'x' in front of the number means it's hexadecimal, else decimal.
        if (match[1].length() == 1)
        {
            codepoint = std::stoi(match[2].str(), nullptr, 16);
        }
        else
        {
            codepoint = std::stoi(match[2].str(), nullptr, 10);
        }
        output += match.prefix().str() + u8c.to_bytes(codepoint);
        buffer = match.suffix().str();
    }
    output += buffer;

    // Source: https://en.wikipedia.org/wiki/List_of_XML_and_HTML_character_
    //         entity_references#Character_entity_references_in_HTML
    const std::array<const std::pair<const string, const char32_t>, 258> names =
    {{
        { "exclamation", 0x0021 },
        { "quot", 0x0022 },
        { "percent", 0x0025 },
        { "amp", 0x0026 },
        { "apos", 0x0027 },
        { "add", 0x002B },
        { "lt", 0x003C },
        { "equal", 0x003D },
        { "gt", 0x003E },
        { "nbsp", 0x00A0 },
        { "iexcl", 0x00A1 },
        { "cent", 0x00A2 },
        { "pound", 0x00A3 },
        { "curren", 0x00A4 },
        { "yen", 0x00A5 },
        { "brvbar", 0x00A6 },
        { "sect", 0x00A7 },
        { "uml", 0x00A8 },
        { "copy", 0x00A9 },
        { "ordf", 0x00AA },
        { "laquo", 0x00AB },
        { "not", 0x00AC },
        { "shy", 0x00AD },
        { "reg", 0x00AE },
        { "macr", 0x00AF },
        { "deg", 0x00B0 },
        { "plusmn", 0x00B1 },
        { "sup2", 0x00B2 },
        { "sup3", 0x00B3 },
        { "acute", 0x00B4 },
        { "micro", 0x00B5 },
        { "para", 0x00B6 },
        { "middot", 0x00B7 },
        { "cedil", 0x00B8 },
        { "sup1", 0x00B9 },
        { "ordm", 0x00BA },
        { "raquo", 0x00BB },
        { "frac14", 0x00BC },
        { "frac12", 0x00BD },
        { "frac34", 0x00BE },
        { "iquest", 0x00BF },
        { "Agrave", 0x00C0 },
        { "Aacute", 0x00C1 },
        { "Acirc", 0x00C2 },
        { "Atilde", 0x00C3 },
        { "Auml", 0x00C4 },
        { "Aring", 0x00C5 },
        { "AElig", 0x00C6 },
        { "Ccedil", 0x00C7 },
        { "Egrave", 0x00C8 },
        { "Eacute", 0x00C9 },
        { "Ecirc", 0x00CA },
        { "Euml", 0x00CB },
        { "Igrave", 0x00CC },
        { "Iacute", 0x00CD },
        { "Icirc", 0x00CE },
        { "Iuml", 0x00CF },
        { "ETH", 0x00D0 },
        { "Ntilde", 0x00D1 },
        { "Ograve", 0x00D2 },
        { "Oacute", 0x00D3 },
        { "Ocirc", 0x00D4 },
        { "Otilde", 0x00D5 },
        { "Ouml", 0x00D6 },
        { "times", 0x00D7 },
        { "Oslash", 0x00D8 },
        { "Ugrave", 0x00D9 },
        { "Uacute", 0x00DA },
        { "Ucirc", 0x00DB },
        { "Uuml", 0x00DC },
        { "Yacute", 0x00DD },
        { "THORN", 0x00DE },
        { "szlig", 0x00DF },
        { "agrave", 0x00E0 },
        { "aacute", 0x00E1 },
        { "acirc", 0x00E2 },
        { "atilde", 0x00E3 },
        { "auml", 0x00E4 },
        { "aring", 0x00E5 },
        { "aelig", 0x00E6 },
        { "ccedil", 0x00E7 },
        { "egrave", 0x00E8 },
        { "eacute", 0x00E9 },
        { "ecirc", 0x00EA },
        { "euml", 0x00EB },
        { "igrave", 0x00EC },
        { "iacute", 0x00ED },
        { "icirc", 0x00EE },
        { "iuml", 0x00EF },
        { "eth", 0x00F0 },
        { "ntilde", 0x00F1 },
        { "ograve", 0x00F2 },
        { "oacute", 0x00F3 },
        { "ocirc", 0x00F4 },
        { "otilde", 0x00F5 },
        { "ouml", 0x00F6 },
        { "divide", 0x00F7 },
        { "oslash", 0x00F8 },
        { "ugrave", 0x00F9 },
        { "uacute", 0x00FA },
        { "ucirc", 0x00FB },
        { "uuml", 0x00FC },
        { "yacute", 0x00FD },
        { "thorn", 0x00FE },
        { "yuml", 0x00FF },
        { "OElig", 0x0152 },
        { "oelig", 0x0153 },
        { "Scaron", 0x0160 },
        { "scaron", 0x0161 },
        { "Yuml", 0x0178 },
        { "fnof", 0x0192 },
        { "circ", 0x02C6 },
        { "tilde", 0x02DC },
        { "Alpha", 0x0391 },
        { "Beta", 0x0392 },
        { "Gamma", 0x0393 },
        { "Delta", 0x0394 },
        { "Epsilon", 0x0395 },
        { "Zeta", 0x0396 },
        { "Eta", 0x0397 },
        { "Theta", 0x0398 },
        { "Iota", 0x0399 },
        { "Kappa", 0x039A },
        { "Lambda", 0x039B },
        { "Mu", 0x039C },
        { "Nu", 0x039D },
        { "Xi", 0x039E },
        { "Omicron", 0x039F },
        { "Pi", 0x03A0 },
        { "Rho", 0x03A1 },
        { "Sigma", 0x03A3 },
        { "Tau", 0x03A4 },
        { "Upsilon", 0x03A5 },
        { "Phi", 0x03A6 },
        { "Chi", 0x03A7 },
        { "Psi", 0x03A8 },
        { "Omega", 0x03A9 },
        { "alpha", 0x03B1 },
        { "beta", 0x03B2 },
        { "gamma", 0x03B3 },
        { "delta", 0x03B4 },
        { "epsilon", 0x03B5 },
        { "zeta", 0x03B6 },
        { "eta", 0x03B7 },
        { "theta", 0x03B8 },
        { "iota", 0x03B9 },
        { "kappa", 0x03BA },
        { "lambda", 0x03BB },
        { "mu", 0x03BC },
        { "nu", 0x03BD },
        { "xi", 0x03BE },
        { "omicron", 0x03BF },
        { "pi", 0x03C0 },
        { "rho", 0x03C1 },
        { "sigmaf", 0x03C2 },
        { "sigma", 0x03C3 },
        { "tau", 0x03C4 },
        { "upsilon", 0x03C5 },
        { "phi", 0x03C6 },
        { "chi", 0x03C7 },
        { "psi", 0x03C8 },
        { "omega", 0x03C9 },
        { "thetasym", 0x03D1 },
        { "upsih", 0x03D2 },
        { "piv", 0x03D6 },
        { "ensp", 0x2002 },
        { "emsp", 0x2003 },
        { "thinsp", 0x2009 },
        { "zwnj", 0x200C },
        { "zwj", 0x200D },
        { "lrm", 0x200E },
        { "rlm", 0x200F },
        { "ndash", 0x2013 },
        { "mdash", 0x2014 },
        { "horbar", 0x2015 },
        { "lsquo", 0x2018 },
        { "rsquo", 0x2019 },
        { "sbquo", 0x201A },
        { "ldquo", 0x201C },
        { "rdquo", 0x201D },
        { "bdquo", 0x201E },
        { "dagger", 0x2020 },
        { "Dagger", 0x2021 },
        { "bull", 0x2022 },
        { "hellip", 0x2026 },
        { "permil", 0x2030 },
        { "prime", 0x2032 },
        { "Prime", 0x2033 },
        { "lsaquo", 0x2039 },
        { "rsaquo", 0x203A },
        { "oline", 0x203E },
        { "frasl", 0x2044 },
        { "euro", 0x20AC },
        { "image", 0x2111 },
        { "weierp", 0x2118 },
        { "real", 0x211C },
        { "trade", 0x2122 },
        { "alefsym", 0x2135 },
        { "larr", 0x2190 },
        { "uarr", 0x2191 },
        { "rarr", 0x2192 },
        { "darr", 0x2193 },
        { "harr", 0x2194 },
        { "crarr", 0x21B5 },
        { "lArr", 0x21D0 },
        { "uArr", 0x21D1 },
        { "rArr", 0x21D2 },
        { "dArr", 0x21D3 },
        { "hArr", 0x21D4 },
        { "forall", 0x2200 },
        { "part", 0x2202 },
        { "exist", 0x2203 },
        { "empty", 0x2205 },
        { "nabla", 0x2207 },
        { "isin", 0x2208 },
        { "notin", 0x2209 },
        { "ni", 0x220B },
        { "prod", 0x220F },
        { "sum", 0x2211 },
        { "minus", 0x2212 },
        { "lowast", 0x2217 },
        { "radic", 0x221A },
        { "prop", 0x221D },
        { "infin", 0x221E },
        { "ang", 0x2220 },
        { "and", 0x2227 },
        { "or", 0x2228 },
        { "cap", 0x2229 },
        { "cup", 0x222A },
        { "int", 0x222B },
        { "there4", 0x2234 },
        { "sim", 0x223C },
        { "cong", 0x2245 },
        { "asymp", 0x2248 },
        { "ne", 0x2260 },
        { "equiv", 0x2261 },
        { "le", 0x2264 },
        { "ge", 0x2265 },
        { "sub", 0x2282 },
        { "sup", 0x2283 },
        { "nsub", 0x2284 },
        { "sube", 0x2286 },
        { "supe", 0x2287 },
        { "oplus", 0x2295 },
        { "otimes", 0x2297 },
        { "perp", 0x22A5 },
        { "sdot", 0x22C5 },
        { "lceil", 0x2308 },
        { "rceil", 0x2309 },
        { "lfloor", 0x230A },
        { "rfloor", 0x230B },
        { "lang", 0x2329 },
        { "rang", 0x232A },
        { "loz", 0x25CA },
        { "spades", 0x2660 },
        { "clubs", 0x2663 },
        { "hearts", 0x2665 },
        { "diams", 0x2666 }
    }};

    for (auto &pair : names)
    {
        const std::regex re('&' + pair.first + ';');
        output = std::regex_replace(output, re, u8c.to_bytes(pair.second));
    }

    return output;
}

void API::set_proxy(const string &proxy, const string &userpw)
{
    _proxy = proxy;
    _proxy_userpw = userpw;
}

void API::get_proxy(string &proxy, string &userpw) const
{
    if (!_proxy.empty())
    {
        proxy = _proxy;
        if (!_proxy_userpw.empty())
        {
            userpw = _proxy_userpw;
        }
    }
}
