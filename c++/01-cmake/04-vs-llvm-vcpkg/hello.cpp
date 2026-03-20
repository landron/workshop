#include <print>
#include <sqlite3.h>

int main()
{
    const auto id = SUBFOLDER;
    std::print("Hello, world, from {}!\nSQLite version: {}\n", id, sqlite3_libversion());
}
