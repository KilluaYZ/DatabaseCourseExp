#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <cstdint>
#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <cstring>
#include <arpa/inet.h>
using namespace std;

const int FRAME_BUF_SIZE = 1024;
const int FRAME_HEAD_SIZE = 6;
const int FRAME_SIZE = FRAME_HEAD_SIZE + FRAME_BUF_SIZE * 2;
const int FRAME_TYPE_UNKNOW = 0;
const int FRAME_TYPE_LIST_KEYS = 1;
const int FRAME_TYPE_GET = 2;
const int FRAME_TYPE_INSERT = 3;
const int FRAME_TYPE_DELETE = 4;
const int FRAME_TYPE_SHUTDOWN = 5;
const int FRAME_TYPE_SAVE = 6;

struct _frame
{
    uint16_t _type;
    uint16_t _key_length;
    uint16_t _val_length;
    char _key_buf[FRAME_BUF_SIZE];
    char _val_buf[FRAME_BUF_SIZE];
};

class Instruction
{
public:
    int type;
    string key;
    string val;

    Instruction(_frame *_f)
    {
        this->type = _f->_type;
        if (this->type == FRAME_TYPE_INSERT || this->type == FRAME_TYPE_GET || this->type == FRAME_TYPE_DELETE)
            this->key = string(_f->_key_buf);
        if (this->type == FRAME_TYPE_INSERT)
            this->val = string(_f->_val_buf);
    }

    Instruction()
    {
        this->type = FRAME_TYPE_UNKNOW;
    }

    Instruction *setType(int _type)
    {
        this->type = _type;
        return this;
    }

    Instruction *setKey(string key)
    {
        this->key = key;
        return this;
    }

    Instruction *setVal(string val)
    {
        this->val = val;
        return this;
    }

    _frame to_frame()
    {
        _frame _f;
        _f._type = this->type;
        memcpy(_f._key_buf, this->key.c_str(), this->key.length());
        memcpy(_f._val_buf, this->val.c_str(), this->val.length());
        _f._key_length = this->key.length();
        _f._val_length = this->val.length();
        return _f;
    }
};

#endif