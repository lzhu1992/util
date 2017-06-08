#pragma once
#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Buffer {
private:
  size_t size;
  char * buffer;
  size_t availSize;
  char *p;
  int fd;
  void checkSize(size_t sz) {
     if(availSize< sz) {
        flush();
     }
  }
  void checkAvailableRead(size_t sz) {
      if (sz > size) {
          readNext();
      }
  }
  void advance(size_t ds) {
		p += ds;
		availSize -= ds;
	}	

public:
  Buffer(const char filename[], size_t initialSize);
  Buffer(const Buffer & c) = delete; 
  void operator =(const Buffer& orig) = delete;
  void flush () {
    write(fd, buffer,p-buffer);
      p = buffer;
      availSize = size;
  }
  void readNext() {
      int bytesRead = read(fd, buffer, size);
  }

//*********************************//
//************ uint8_t *************//
//************ uint16_t *************//
//************ uint32_t *************//
//************ uint64_t *************//
  void write(uint8_t v) {
     *(uint8_t*)p = v;
     advance(sizeof(uint8_t));
  } 
  void write(uint16_t v) {
     *(uint16_t*)p = v;
     advance(sizeof(uint16_t));
  } 
  void write(uint32_t v) {
     *(uint32_t*)p = v;
     advance(sizeof(uint32_t));
  } 
//*********************************//
//************ uint8_t array *************//
//************ uint16_t array *************//
//************ uint32_t array *************//
//************ uint64_t array *************//
template<typename T> 
void checArraySpace(T v[], size_t n) {
  //TODO: efficiency, and for big arrays if (n > ???)
    if(availSize< n*sizeof(T)) {
        flush();
     }
  }
  //*********************************//
//************ uint8_t vector *************//
//************ uint16_t vector *************//
//************ uint32_t vector *************//
//************ uint64_t vector *************//
  void checkWriteMax1(const vector<uint8_t>& v) {
    if(availSize< v.size()*sizeof(v)) {
        flush();
  }
  void checkWriteMax2 (const vector<uint16_t>& v) {
    if(availSize< v.size()*sizeof(v)) {
        flush();
  }
  void checkWriteMax3 (const vector<uint32_t>& v) {
    if(availSize< v.size()*sizeof(v)) {
        flush();
  }
  void checkWriteMax4 (const vector<uint64_t>& v) {
    if(availSize< v.size()*sizeof(v)) {
        flush();
  }
  Buffer& operator <<(uint32_t v) {
    checkSize(sizeof(v));
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
        uint16_t temp = *(uint16_t*)p;
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
        readUint8();
  }

    uint16_t readUint16Check() {
        checkAvailableRead(sizeof(uint16_t));
        readUint16();
  }
    uint32_t readUint32Check() {
    checkAvailableRead(sizeof(uint32_t));
    readUint32();
  }
    uint64_t readUint64Check() {
    checkAvailableRead(sizeof(uint64_t));
    readUint64();
  }

//read array


  Buffer& append(string& s, DataType t) {}

  
};
