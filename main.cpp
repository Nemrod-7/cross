#include <iostream>

int main () {

    std::cout << "This is a test\n";

    if (std::cin.get() == '\n')
        std::cout << "\nexit\n";
}
