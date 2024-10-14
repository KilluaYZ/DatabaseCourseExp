#ifndef MEXCEPTION_HPP
#define MEXCEPTION_HPP

#include <exception>
#include <string>
using namespace std;

class MException : public exception{
private:
    string msg;
public:
    MException(string msg){
        this->msg = msg;
    }

    virtual ~MException() noexcept {}

    virtual const char* what() const noexcept override{
        return msg.c_str();
    }
};


#endif 