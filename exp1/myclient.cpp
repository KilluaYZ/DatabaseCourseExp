
#include <iostream>
#include "socket.hpp"

using namespace std;

int main(void)
{
    try
    {
        
        Socket::FileSocket sock;
        sock.bind(3000);
        sock.send("127.0.0.1", 2000, "/home/dte/NetCourseExp/exp1/server/file");
        sock.close();
    }
    catch (Socket::Exception &e)
    {
        cout << e.what() << endl;
    }
    
    return 0;
}