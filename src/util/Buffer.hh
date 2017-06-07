/**
	 A binary high-speed buffer to support writing objects portably to a
	 binary stream so it can be read back in (persistence)

 */
#pragma once
#include <cstdint>
#include <cstring>
#include<iostream>
#include<fstream>
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
void checkWrite1(uint8_t[] v, size_t n) {
    if(availSize< n*sizeof(v)) {
        flush();
     }
  }
  void checkWrite2(uint16_t[] v, size_t n) {
    if(availSize< n*sizeof(v)) {
        flush();
     }
  }
  void checkWrite3(uint32_t[] v, size_t n) {
    if(availSize< n*sizeof(v)) {
        flush();
     }
  }
  void checkWrite4(uint64_t[] v, size_t n) {
    if(availSize< n*sizeof(v)) {
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

 

  Buffer& append(string& s, DataType t) {}

  
};
 