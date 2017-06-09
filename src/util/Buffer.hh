#pragma once
#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
using namespace std;
class Buffer {
private:
  size_t size;
  char * buffer;
  size_t availSize;
  char *p;
  int fd;
  void checkSpace(size_t sz) {
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
//************ uint8_t uint16_t uint32_t uint64_t *************//
template<typename T>
  void write(T v) {
     *(T*)p = v;
     advance(sizeof(T));
  }
    //*********************************//
//************ uint8_t uint16_t uint32_t uint64_t array *************//
//*********************************//
    void checkSpace(size_t sz) {
        if(availSize< sz) {
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
  void checkVectorSpace(const vector<T>& v) {
    if(availSize< v.size()*sizeof(T)) {
        flush();
  }
      //*********************************//
//************ uint8_t uint16_t uint32_t uint64_t operator *************//
      Buffer& operator <<(T v) {
          checkSpace(sizeof(T));
          write(v);
          return *this;
      }

// readUnit8,readUnit16,readUnit32,readUnit64
    T readUint() {
        T temp = *(T*)p;
        p += sizeof(T);
        availSize -= sizeof(T);
        return temp;
  }


//read Uint8Check,readUint16Check,readUint32Check,readUint64Check
    T readUintCheck() {
        checkAvailableRead(sizeof(T));
        readUint();
  }

  Buffer& append(string& s, DataType t) {}

  
};
