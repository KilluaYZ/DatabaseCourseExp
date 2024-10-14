#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "MException.hpp"
#include "SocketStorage.hpp"

using namespace std;

class Client
{
private:
  SocketStorage *_store;
  Socket::Ip ip;
  Socket::Port port;

  void send(Instruction *inst, bool wait_resp = true)
  {
    if (_store == nullptr)
      throw MException("_store is null");
    this->_store->send(this->ip, this->port, inst);
    if (wait_resp)
    {
      Socket::Datagram dg = this->_store->sock.receive();
      string msg = string(dg.data.buf, dg.data.size);
      cout << msg << endl;
    }
  }

public:
  Client(Socket::Ip ip, Socket::Port port)
  {
    this->ip = ip;
    this->port = port;
    this->_store = new SocketStorage();
  }

  ~Client()
  {
    delete this->_store;
  }

  vector<string> split_str(string _str)
  {
    vector<string> words;
    string word;
    istringstream iss(_str);
    while (iss >> word)
    {
      words.push_back(word);
    }
    return words;
  }

  void parse(string buf)
  {
    if (buf.empty())
      return;
    vector<string> splited_str = split_str(buf);
    if (splited_str.size() == 0)
    {
      throw MException("Unexpeted Error");
      return;
    }
    string cmd = splited_str[0];
    if (cmd == "find")
    {
      if (splited_str.size() != 2)
        throw MException("Unmatched args number");
      string key = splited_str[1];
      Instruction *inst = new Instruction();
      inst->setType(FRAME_TYPE_GET);
      inst->setKey(key);
      send(inst);
      delete inst;
    }
    else if (cmd == "insert")
    {
      if (splited_str.size() != 3)
        throw MException("Unmatched args number");
      string key = splited_str[1];
      string val = splited_str[2];
      Instruction *inst = new Instruction();
      inst->setType(FRAME_TYPE_INSERT);
      inst->setKey(key);
      inst->setVal(val);
      send(inst);
      delete inst;
    }
    else if (cmd == "delete")
    {
      if (splited_str.size() != 2)
        throw MException("Unmatched args number");
      string key = splited_str[1];
      Instruction *inst = new Instruction();
      inst->setType(FRAME_TYPE_DELETE);
      inst->setKey(key);
      send(inst);
      delete inst;
    }
    else if (cmd == "show")
    {
      if (splited_str.size() != 1)
        throw MException("Unmatched args number");
      Instruction *inst = new Instruction();
      inst->setType(FRAME_TYPE_LIST_KEYS);
      send(inst);
      delete inst;
    }
    else if (cmd == "quit")
    {
      cout << "bye~" << endl;
      exit(0);
    }
    else if (cmd == "shutdown")
    {
      if (splited_str.size() != 1)
        throw MException("Unmatched args number");
      Instruction *inst = new Instruction();
      inst->setType(FRAME_TYPE_SHUTDOWN);
      send(inst, false);
      delete inst;
      cout << "Server is down, So client will quit soon" << endl;
      exit(0);
    }
    else if (cmd == "save")
    {
      if (splited_str.size() != 1)
        throw MException("Unmatched args number");
      Instruction *inst = new Instruction();
      inst->setType(FRAME_TYPE_SAVE);
      send(inst);
      delete inst;
    }
    else if (cmd == "help")
    {
      if (splited_str.size() != 1)
        throw MException("Unmatched args number");
      cout << "Usage: " << endl 
      << "help: \t\t\t show this help info." << endl
      << "insert <key> <value>: \t insert a record." << endl
      << "find <key>: \t\t get value." << endl
      << "delete <key>: \t\t delete the record." << endl
      << "show: \t\t\t show all records in server." << endl
      << "save: \t\t\t save the records to a file." << endl
      << "quit: \t\t\t quit client." << endl
      << "shutdown: \t\t close the remote server." << endl;
    }
    else
    {
      cout << "Invalid Operation" << endl;
    }
  }

  void start()
  {
    cout << "Welcome to TinyDB, type \033[32mhelp\033[0m to view the usage." << endl;
    while (true)
    {
      try
      {
        string buf;
        cout << "\033[32mTinyDB$ \033[0m";
        getline(cin, buf);
        parse(buf);
      }
      catch (MException &e)
      {
        cout << e.what() << endl;
      }
    }
  }
};

#endif
