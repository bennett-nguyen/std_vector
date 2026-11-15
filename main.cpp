#include <iostream>
#include <string>
#include "vector.h"

int main() {
    std::string hello = "Hello world";
    std::string zzz = "me may beo";
    Vector<std::string> messages {};
    messages.push_back(hello);
    messages.push_back(zzz);

    for (size_t i = 0; i < messages.size(); i++) {
        std::cout << messages[i] << '\n';
    }
}