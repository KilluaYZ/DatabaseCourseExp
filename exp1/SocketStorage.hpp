#ifndef SOCKET_STORAGE_HPP
#define SOCKET_STORAGE_HPP

#include "Socket.hpp"
#include "Instruction.hpp"
#include <thread>
#include "Storage.hpp"

using namespace std;

class SocketStorage
{
private:
    Storage *_store;

    static void process_inst(Socket::Ip recv_ip, Socket::Port recv_port, Storage* _store, Socket::UDP sock, Instruction *inst)
    {
        string res = "";
        try
        {
            switch (inst->type)
            {
            case FRAME_TYPE_GET:
                res = _store->_find(inst->key);
                break;
            case FRAME_TYPE_INSERT:
                _store->_insert(inst->key, inst->val);
                res = "Insert Success";
                break; 
            case FRAME_TYPE_DELETE:
                _store->_delete(inst->key);
                res = "Delete Success";
                break;
            case FRAME_TYPE_LIST_KEYS:
                res = _store->_list_keys();
                break;
            case FRAME_TYPE_SAVE:
                _store->save();
                res = "Save Success";
                break;
            case FRAME_TYPE_SHUTDOWN:
                cout << "bye~" << endl;
                exit(0); 
            default:
                res = "Unknow Operation";
                break;
            }
        }
        catch (MException& e){
            res = e.what();
        }
        catch (exception& e)
        {
            res = "Unexpected Error Occured!";
        }
        sock.send(recv_ip, recv_port, res);
        delete inst;
    }

public:
    Socket::UDP sock;
    SocketStorage()
    {
    }

    void init_storage(string store_path)
    {
        _store = new Storage(store_path);
    }

    // get instruction
    void recv()
    {
        Socket::Datagram dg = sock.receive();
        Instruction *inst = new Instruction((_frame *)dg.data.buf);
        thread(process_inst, dg.address.ip, dg.address.port, this->_store, this->sock, inst).join();
    }

    // send instruction
    void send(Socket::Ip ip, Socket::Port port, Instruction *inst)
    {
        Socket::Data* data = new Socket::Data();
        _frame _f = inst->to_frame();
        memcpy(data->buf, &_f, sizeof(_f));
        data->size = sizeof(_f);
        sock.send(ip, port, data);
        delete data;
    }

    void bind(Socket::Port port){
        sock.bind(port);
    }
};

#endif