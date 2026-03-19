
// std::cout is "Heavy": The <iostream> library is notorious for slow compile times and a clunky interface.
// #include <iostream>
#include <print>

int main() {
    std::println("Hello World!"); 
    // std::println automatically adds the newline and is more efficient than cout.
}
