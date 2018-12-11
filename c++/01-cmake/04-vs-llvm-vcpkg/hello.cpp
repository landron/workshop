#include <iostream>
#include <sqlite3.h>

int main()
{
    std::cout << "Hello sqlite3 " << sqlite3_libversion() << '!' << std::endl;
    return 0;
}