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


  void write(uint32_t v) {
		*(uint32_t*)p = v;
		advance(sizeof(uint32_t));
  } 

  Buffer& operator <<(uint32_t v) {
    checkSize(sizeof(v));
    write(v);
    return *this;    
  }

  void write(uint32_t[] v, size_t n) {
    for (size_t i = 0; i < n; i++) {
        *(uint32_t*)p = v[i];
        p += sizeof(v);
    }
    availSize -= n * sizeof(v);
  } 
  void checkWrite(uint32_t[] v, size_t n) {
  }

  uint32_t readUint32() {

  }

  Buffer& append(string& s, DataType t) {}

  void writeUint1array(uint8_t x[], int n) {
        p = buffer;
        buffer = new char[Size+1];
        for(int i = 0; i < n ;i++) {
            *p = i;
        }
        Avail_size= Size - n * sizeof(uint8_t);
        for(int i = 0; i < n;i++) {
            buffer =uint8_t[i] ;
            buffer++;
        }
        if(Avail_size < 0) {
             flush(buffer);
        }
        else {
             write(buffer);
    }
  void writeString(string s) {
    availSize= size - s.length();
    for(int i = 0; i < s.length(); i++) {
            buffer = s.at(i);
            buffer++;
        }
        for(int i = 0; i < s.length() ;i++) {
            *p = i;
        }
            if(Avail_size < 0) {
                flush(buffer);
            }
            else {
                write(buffer);
            }
        }
};
  int main() {
    Buffer a = ;
    cout<<"a: "<<a<<endl;
    return 0;
}


   /* void flush {
	    write();
	    p = buf;
	    available = size;
    } 
    void write () {
    }
    void writemeta() {
    }*/
	    
  
    //Buffer(int initialSize, const char * initialSize) {
        
    }//
};
Buffer::Buffer(int initialSize) {
	data = new char[initialSize];
	data[0] = 0;
	size = initialSize;
	length = 0;
}

Buffer::Buffer(int initialSize, const char * initialValue) {
	data = new char[initialSize];
	size = initialSize;
	length = 0;
	do {
		data[length] = initialValue[length];
	} while (initialValue[length++] != 0);
}

#if  0
/*
 * Create Buffer initialized with http headers with embedded mime type
 */
char* Buffer::Buffer(size_t initialsize, const char* header, size_t size,
										 const string& mimeType) {
	data = new char[initialSize];
	size = initialSize;	
  char* buf = data;
	memcpy(buf, header, size);
	buf += size;
	memcpy(buf, mimeType.c_str(), mimeType.length());
	buf += mimeType.length();
	memcpy(buf, "\r\n\r\n", 4);
  length = buf - data;
}
#endif

void Buffer::append(double v[],int number,const std::string& sep){
	checkSpace(number*(20+sep.length()));
	for (int i = 0;i < number-1;i++){
		length += sprintf(data+length,"%lf%s",v[i],sep.c_str());		
	}
} 
