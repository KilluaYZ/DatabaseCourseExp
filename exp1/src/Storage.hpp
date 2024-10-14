#ifndef STORAGE_HPP
#define STORAGE_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "MException.hpp"
using namespace std;

template <typename K, typename V>
void serialize(const std::unordered_map<K, V>& map, const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw MException("unabled to open file");
    }
    for (const auto& pair : map) {
        ofs << pair.first << " " << pair.second << std::endl;
    }
}

template <typename K, typename V>
void deserialize(std::unordered_map<K, V>& map, const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw MException("unabled to open file");
    }
    K key;
    V value;
    while (ifs >> key >> value) {
        map[key] = value;
    }
}

class Storage
{
private:
    string store_path;
    unordered_map<string, string> _map;    
public:
    Storage(string store_path){
        this->store_path = store_path;
        try{
            load();
        }catch(exception& e){

        }
    }

    void _insert(string _key, string _val){
        auto it = _map.find(_key);
        if(it != _map.end()) throw MException("The record is already existed");
        _map[_key] = _val;
    }

    void _delete(string _key){
        auto it = _map.find(_key);
        if(it == _map.end()) throw MException("The record is not exists");
        _map.erase(it);
    } 

    string _find(string _key){
        auto it = _map.find(_key);
        if(it == _map.end()) throw MException("Null");
        return it->second; 
    }

    string _list_keys(){
        if(_map.size() == 0) return "Empty";
        stringstream ss;
        ss << "Keys: ";
        for(auto it = _map.begin(); it != _map.end(); it++){
            ss << it->first << ", "; 
        }
        return ss.str();
    }

    void save(){
        serialize<string, string>(this->_map, this->store_path);
    }

    void load(){
        deserialize<string, string>(this->_map, this->store_path); 
    }
};

#endif