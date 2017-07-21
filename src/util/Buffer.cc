#include <cstring>
#include <vector>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "Buffer.hh"
using namespace std;

Buffer::Buffer(size_t initialSize, bool writing) : size(initialSize), writing(writing) {
    preBuffer = new char[size+extra*2];
    buffer = extra+preBuffer;
    p = buffer;
		fd = -1;		
}

Buffer::Buffer(const char filename[], size_t initialSize) : Buffer(initialSize, true) {
	availSize = size;
    fd = creat(filename, 0664);
    if (fd < 0)
        throw "File cannot write";
}
Buffer::Buffer(const char filename[], size_t initialSize, const char*)  : Buffer(initialSize, false) {
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        throw "File cannot open";
		availSize = 0;
    writing = false;
}

Buffer::~Buffer() {
    if (writing)
        flush();
    delete[] preBuffer;
    int status = close(fd);
}

void Buffer::readNext() {
    availSize = ::read(fd, buffer, size);
}
void Buffer:: flush () {//how to copy
    ::write(fd, buffer,size);
    size_t overSize = p - (buffer + size);
    memcpy(buffer,buffer+size, overSize);
    p = buffer + overSize;
    availSize = size - overSize;
}



void Buffer::write(const string& s) {
    if(s.length() < 256) {
        *(uint8_t*)p++ = s.length();
    }else if (s.length() < 65536){
        *(uint16_t*)p++ = s.length();
    } else {
        *(uint32_t*)p++ = s.length();
    }
    for(uint8_t i = 0; i < s.length();i++) {
        *p++ = s[i];
    }
    availSize -= s.length();
}


string Buffer::readstring1() {
    uint8_t len = *(uint8_t *)p;
    p += sizeof(uint8_t);
    string s;
    s.reserve(len);
    for (size_t i = 0 ; i < len; i++){
        s += *p;
        p += sizeof(uint8_t);
    }
    return s;
}
string Buffer::readstring2() {
    uint16_t len = *(uint16_t *)p;
    p += sizeof(uint16_t);
    string s;
    s.reserve(len);
    for (size_t i = 0 ; i < len; i++){
        s += *p;
        p += sizeof(uint16_t);
    }
    return s;
}
string Buffer::readstring4() {
    uint32_t len = *(uint32_t *)p;
    p += sizeof(uint32_t);
    string s;
    s.reserve(len);
    for (size_t i = 0 ; i < len; i++){
        s += *p;
        p += sizeof(uint32_t);
    }
    return s;
}
StringBuffer::StringBuffer(size_t initialSize) : size(initialSize) {
    s = new char[size];
    availSz = size;
    cursor = s;
    size_t availSz;
}
StringBuffer::~StringBuffer() {
    // don't know how to write
}
void StringBuffer:: flush () {
    cursor = s;
    availSz = size;
}
void StringBuffer:: appendUInt8(uint8_t v){
    uint8_t len = sprintf(cursor,"%d",v);
    cursor += len;
    availSz -= len;
}
/*
void Buffer::append(double v[],int number,const std::string& sep){
    checkSpace(number*(20+sep.length()));
    for (int i = 0;i < number-1;i++){
        length += sprintf(data+length,"%lf%s",v[i],sep.c_str());
    }
}
};
 */
