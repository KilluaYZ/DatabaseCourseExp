
#include <iostream>
#include "Server.hpp"

using namespace std;

int main(void)
{
    Server server("tinydb.bin", 10020);
    server.start_service();
    return 0;
}