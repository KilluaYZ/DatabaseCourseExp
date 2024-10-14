#ifndef SOCKET_STORAGE_HPP
#define SOCKET_STORAGE_HPP

#include "socket.hpp"
#include "Instruction.hpp"
#include <thread>
#include "Storage.hpp"

using namespace std;

class SocketStorage
{
private:
    Socket::UDP sock;
    Storage *_store;

    void process_inst(Socket::Ip recv_ip, Socket::Port recv_port, Instruction *inst)
    {
        string res = "Success!";
        try
        {
            switch (inst->type)
            {
            case FRAME_TYPE_GET:
                res = this->_store->_find(inst->key);
                break;
            case FRAME_TYPE_INSERT:
                this->_store->_insert(inst->key, inst->val);
                break; 
            case FRAME_TYPE_DELETE:
                this->_store->_delete(inst->key);
            case FRAME_TYPE_LIST_KEYS:
                res = this->_store->_list_keys();
            default:
                res = "Unknow Operation";
                break;
            }
        }
        catch (exception e)
        {
            res = "Error Occured!";
        }
        this->sock.send(recv_ip, recv_port, res);
        free(inst);
    }

public:
    SocketStorage()
    {
    }

    void init_storage(string store_path)
    {
        this->_store = new Storage(store_path);
    }

    // get instruction
    void recv()
    {
        Socket::Datagram dg = sock.receive();
        Instruction *inst = new Instruction((_frame *)dg.data.buf);
        thread(process_inst, dg.address.ip, dg.address.port, inst);
    }

    // send instruction
    void send(Socket::Ip ip, Socket::Port port, Instruction *inst)
    {
        Socket::Data* data = new Socket::Data();
        _frame _f = inst->to_frame();
        memcpy(data->buf, &_f, sizeof(_f));
        sock.send(ip, port, data);
    }

    void bind(Socket::Port port){
        sock.bind(port);
    }
};

#endif