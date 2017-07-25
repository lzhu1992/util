#pragma once

#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <regex>
using namespace std;
class Buffer {
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
			size_t overflowSize = availSize;
			memcpy(buffer - overflowSize, p, overflowSize);
			readNext();
			availSize += overflowSize;
			p = buffer - overflowSize;
		}
	}
public:
	Buffer(size_t initialSize, bool writing);
	Buffer(const char filename[], size_t initialSize);
	Buffer(const char filename[], size_t initialSize, const char*);
	Buffer(const Buffer & c) = delete;
	void attach(int sockfd) { fd = sockfd; }
	~Buffer();
	void operator =(const Buffer& orig) = delete;
	void flush ();
	void readNext();
	void write(const string& s);
    void appendUInt8(uint8_t);
    bool parseRegex(const regex& r, const char*& start, int& len);
	// if parse returns true, advance past the token
    bool parseToken(const string& match);
	/**
		 extract the next space-delimited value from the buffer
		 if return true, this means ptr is pointing to the text, len = the length of the token
		 (until the next space) and the current pointer advances past the token
	*/
	bool getNextToken(const char*&ptr, const uint32_t& len);
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
    Buffer& operator <<(T v) {// there is a write in flush function
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