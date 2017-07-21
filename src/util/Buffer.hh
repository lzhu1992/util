#pragma once

#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>

using namespace std;
class Buffer2 {
private:
    bool writing;
    size_t size;
    const size_t extra = 128;
    char *preBuffer;
    char * buffer;     // pointer to the buffer
    size_t availSize;  // how much space is left in the buffer
    char *p;           // cursor to current byte for reading/writing
    int fd;            // file descriptor for file backing this buffer (read or write)
    void checkAvailableRead(size_t sz) {
        if (availSize < sz) {
            size_t overflowSize = sz - availSize;
            memcpy(buffer - overflowSize, p, overflowSize);
            readNext();
            p = buffer - overflowSize;
        }
    }
public:
    Buffer2(const char filename[], size_t initialSize);
    Buffer2(const char filename[], size_t initialSize, const char*);
    Buffer2(const Buffer2 & c) = delete;
    ~Buffer2();
    void operator =(const Buffer2& orig) = delete;
    void flush ();
    void readNext();
    void write(const string& s);
    string readstring1();
    string readstring2();
    string readstring4();

//*********************************//
//************ uint8_t uint16_t uint32_t uint64_t *************//
    template<typename T>
    void write(T v) {
        *(T*)p = v;
        checkSpace(sizeof(T));
    }
    //*********************************//
//************ uint8_t uint16_t uint32_t uint64_t array *************//
//*********************************//
    void checkSpace(size_t sz) {
        if(p > buffer+size) {
            flush();
        }
    }
    //*********************************//
//************ uint8_t uint16_t uint32_t uint64_t array *************//

    template<typename T>
    void checArraySpace(T v[], size_t n) {
        //TODO: efficiency, and for big arrays if (n > ???)
        if(availSize< n*sizeof(T)) {
            flush();
        }
    }
    //*********************************//
//************ uint8_t uint16_t uint32_t uint64_t vector *************//
    template<typename T>
    void checkVectorSpace(const vector<T>& v) {
        if(availSize< v.size()*sizeof(T))
            flush();
    }

    //*********************************//
//************ uint8_t uint16_t uint32_t uint64_t operator *************//
    template<typename T>
    Buffer2& operator <<(T v) {// there is a write in flush function
        checkSpace(sizeof(T));
        write(v);
        return *this;
    }

// readUnit8,readUnit16,readUnit32,readUnit64
    uint8_t readUint8() {
        uint8_t temp = *(uint8_t*)p;
        p += sizeof(uint8_t);
        availSize -= sizeof(uint8_t);
        return temp;
    }
    uint16_t readUint16() {
        uint8_t temp = *(uint16_t*)p;
        p += sizeof(uint16_t);
        availSize -= sizeof(uint16_t);
        return temp;
    }
    uint32_t readUint32() {
        uint32_t temp = *(uint32_t*)p;
        p += sizeof(uint32_t);
        availSize -= sizeof(uint32_t);
        return temp;
    }
    uint64_t readUint64() {
        uint64_t temp = *(uint64_t*)p;
        p += sizeof(uint64_t);
        availSize -= sizeof(uint64_t);
        return temp;
}

//read Uint8Check,readUint16Check,readUint32Check,readUint64Check
    uint8_t readUint8Check() {
        checkAvailableRead(sizeof(uint8_t));
        return readUint8();
    }
    uint16_t readUint16Check() {
        checkAvailableRead(sizeof(uint16_t));
        return readUint16();
    }
    uint32_t readUint32Check() {
        checkAvailableRead(sizeof(uint32_t));
        return readUint32();
    }
    uint64_t readUint64Check() {
        checkAvailableRead(sizeof(uint64_t));
        return readUint64();
    }
};
// StringBuffer
class StringBuffer{
private:
    char *s;
    char * cursor;
    size_t size;
    size_t availSz;
public:
    StringBuffer(size_t initialSize);
    StringBuffer(const StringBuffer & c) = delete;
    ~StringBuffer();
    void flush();
    void appendUInt8(uint8_t);
};