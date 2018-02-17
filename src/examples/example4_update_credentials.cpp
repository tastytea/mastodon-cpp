/*  This file is part of mastodon-cpp.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include "../mastodon-cpp.hpp"

using Mastodon::API;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <instance> <access token>\n";
        return 1;
    }

    Mastodon::API masto(argv[1], argv[2]);
    masto.set_useragent("mastodon-cpp-example/1.3.3.7");
    std::string answer;
    std::uint16_t ret;
    // This is the Gimp icon, 24x24px, GPL-3
    const std::string avatar =
"data:image/png;base64,"
"iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAABHNCSVQICAgIfAhkiAAAAAlwSFlz"
"AAAN1wAADdcBQiibeAAAABl0RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAAAAMdEVY"
"dFRpdGxlAEZvbGRlcuNZL58AAAAUdEVYdEF1dGhvcgBKYWt1YiBTdGVpbmVy5vv3LwAAACF0RVh0"
"U291cmNlAGh0dHA6Ly9qaW1tYWMubXVzaWNoYWxsLmN6aWbjXgAAAFJ0RVh0Q29weXJpZ2h0AEND"
"IEF0dHJpYnV0aW9uLVNoYXJlQWxpa2UgaHR0cDovL2NyZWF0aXZlY29tbW9ucy5vcmcvbGljZW5z"
"ZXMvYnktc2EvMy4wL16DWrwAAARFSURBVEiJtZXNbxtFGMafGe+ud9eO7bXbNBsSNx9GSaW2aQgK"
"UDiQUmQJiQsHJETFhVNBKuLAhQviT0Aq6g0heqjUS4UQqhYJhCrxoUZKQakIJTFuTGzXjmN7d+31"
"endnhwNNiEIKRWpeaTSjmdHzm/cZzbwkn8/jIIMeqDoA4VGIVCqVZ0DxUuAFn2Wz2dXda/tmUC6X"
"z21sbGQfRrxarb4Mig8BvEkpHdy7vi+AUvokpfSNUqmk/8fJXyeEvD8xNvpcTFUzlNLI3j37W0Rx"
"WKDC/OnTT72gaRoAIJ4YuJ3OaLpl2ZptWtRnjOsjQ1m3a49kUgmp1TJ5FyAPBwCk+bmZ6ZHRUWly"
"YjISi8WkWv3erOd78tkzL0paSiPVaoX//NMiGvUaOrZJ/qG8F2AYBs3n8yEApBKpiBKLq6dmTglj"
"Y+OQJJEoSjSZyRzG1NQxqKoKXdeJqkRx8+Z36PU6D7Rx5w6i0ehkvdH4qLRR/mpk9LFnj5+YEaem"
"j/Hx8Qly7drnxHF6GDoyBMYYlpaWcPHix2i1TRD85QslhP9rBkktee6t8+df5cDg2todDA8PE0VW"
"cOnSJVy5cgXvXHgbAOA4Dq5evYobN24gNzkBgIA80KBdAOazCcZYYkjX6fXrX3JVpFAVOTI39wRU"
"VUIyNYDVtV+RSKaxcGYBs7OzqNc2sFEqwrYsBCFzGWHhAwEAbl++fHkhlTmk3C3+TkK3jaDfhqYl"
"Ydk9tBoVCIIAKSpDllWwkGHxx+9BwdFxfe55QYsxFhqGIQAIt+9zB0AixFwv3Q3anS7cfh89x0Fz"
"8x563SZ6bgh1IA3f9yH1qoj5W2i4IhyzBzWlo+/58INADdxgAEAMQN8wDD+fz7MdAGf8iyAIT7S3"
"Gq9FBKoFYQjXC8A40Gya8Co1MMZAmYsMNbFwpIn+oQgKbhc9VyYkCFYty4oDyAAwAXQNwwgjuVwO"
"ALC8vNyhsnwnoShxRVGyw/qgeiiTJqIoggAIfB+EAJwIECQZHQ/QxD5mkm2kFBHlXkxumu6iZdtV"
"AP79FuwACoUC6TtOJx6PFwWBmv2ADRNCU4TSiBAREFNVpFIaUuk0lHgagXIEdTtEyQz5b20Z82df"
"ERgRp5LJ5POapvXDMCw6jtPdAeRyORQKBViW1REEsciBdcZ4xbS6TttywqbVxWbTJvWtNq1utru1"
"hrleavSKf1j4utzsf2K7XG+1WpOU0izn/HFZlr/Z3Nys7P0qQgBurVYrO45z3XXcHyRJ0kRRHGCM"
"xQMeKAAID7jnc26HnucxxqxOp7Nle7/cSiQGLoii9HQYhkc9zxsEECH7VTTDMHYe6P2eAJABSAA4"
"gOC+x9uvlwPg09PTR2VZfo9zftyyrA+KxeK3+wL2C8MwKP7+Wvguceyaw8mTJ8cIIe96nvfpysrK"
"rYcG/J+oVqvjAOq6rncfScncG7quF7fHB170DxzwJ8uH9gSkOVdYAAAAAElFTkSuQmCC";

    API::parametermap params =
    {
        { "display_name", { "Botty McBotface" } },
        { "note", { "Beep Bop." } },
        { "avatar", { avatar } }
    };
    
    ret = masto.patch(API::v1::accounts_update_credentials, params, answer);
    if (ret == 0)
    {
        std::cout << answer << '\n';
    }
    else if (ret == 3)
    {
        std::cerr << "The URL has permanently changed.\n" <<
                     "New URL: " << answer << '\n';
        return ret;
    }
    else
    {
        std::cerr << "Error code: " << ret << '\n';
        return ret;
    }

    return 0;
}
