#include <iostream>
#include <string>
#include "vector.h"

int main() {
    std::string hello = "Hello world";
    std::string zzz = "me may beo";
    std::string abc = "abc";
    Vector<std::string> messages {};

    messages.push_back(hello);
    messages.push_back(zzz);
    messages.push_back(abc);

    for (auto it = messages.rbegin(); it != messages.rend(); ++it) {
        std::cout << *it << '\n';
    }
}