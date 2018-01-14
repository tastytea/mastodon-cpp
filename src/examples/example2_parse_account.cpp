/*  This file is part of mastodon-cpp.
 *  This example parses your account data and prints it out in a readable way.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../mastodon-cpp.hpp"

using Mastodon::API;
namespace pt = boost::property_tree;
using std::cout;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], argv[2]);
    std::string answer;
    std::uint16_t ret;

    ret = masto.get(API::v1::accounts_verify_credentials, answer);
    if (ret == 0)
    {
        std::istringstream iss(answer);
        pt::ptree tree;
        
        pt::read_json(iss, tree);
        std::string uid = tree.get<std::string>("id");
        cout << "Your ID is: " << uid << '\n';
        cout << "Your whole acount tree:\n";
        
        for (const pt::ptree::value_type &v : tree.get_child(""))
        {
            cout << "    ";
            if (v.second.size() > 0)
            {
                cout << v.first.data() << ": \n";
                for (const pt::ptree::value_type &vc : v.second.get_child(""))
                {
                    cout << "        ";
                    cout << vc.first.data() << ": " << vc.second.data() << '\n';
                }
            }
            else
            {
                cout << v.first.data() << ": " << v.second.data() << '\n';
            }
        }
    }
    else
    {
        std::cerr << "Error code: " << ret << '\n';
        return ret;
    }

    return 0;
}
