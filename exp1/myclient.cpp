
#include <iostream>
#include "Client.hpp"

using namespace std;

int main(void)
{
    Client client("127.0.0.1", 10020);
    client.start();
    return 0;
}