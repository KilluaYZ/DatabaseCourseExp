#ifndef STORAGE_HPP
#define STORAGE_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;
class Storage
{
private:
    string store_path;
    unordered_map<string, string> _map;    
public:
    Storage(string store_path){}

    void _insert(string _key, string _val){
        auto it = _map.find(_key);
        if(it != _map.end()) throw exception();
        _map[_key] = _val;
    }

    void _delete(string _key){
        auto it = _map.find(_key);
        if(it == _map.end()) throw exception();
        _map.erase(it);
    } 

    string _find(string _key){
        auto it = _map.find(_key);
        if(it == _map.end()) throw exception();
        return it->second; 
    }

    string _list_keys(){
        stringstream ss;
        ss << "Keys: ";
        for(auto it = _map.begin(); it != _map.end(); it++){
            ss << it->first << ", "; 
        }
        return ss.str();
    }
};

#endif