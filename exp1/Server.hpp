#ifndef SERVER_HPP
#define SERVER_HPP
#include "SocketStorage.hpp"
#include <string>
using namespace std;

class Server{
private:
    SocketStorage* _store;
public:
    Server(string store_path, Socket::Port port){
        _store = new SocketStorage();
        _store->init_storage(store_path);
        _store->bind(port);
    }

    void start_service(){
        while(true){
            this->_store->recv();
        }
    }

    ~Server(){
        free(_store);
    }
};

#endif