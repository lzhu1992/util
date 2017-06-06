/*
 * Buffer.cpp
 *
 *  Created on: March 22, 2015
 *      Author: Dov Kruger
 */

#include "Buffer.hh"
#include <cstring>
#include<iostream>
#include<fstream>
#include<string>
#include<iostream>
using namespace std;
class Buffer {
private:
    int Size;
    char * buffer;
    long Avail_size;
    char *p;
public:
    Buffer() {
        buffer = new char[Size];
        buffer[0] = 0;
        Avail_size = Size;
          }
    ~Buffer() {
        delete[] buffer;
    }
   
    void write (char* buffer){
            ofstream out("/Users/zhulin/Desktop/CSP/data.txt");
            if(!out) {
                return;
            }
            out.write(buffer,Size);
            out.close();
        
    }
    void flush (char* buffer) {
        write(buffer);
        p = buffer;
        Avail_size = Size;
    }

    void writeUint1(uint8_t [], int n) {
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
        Avail_size= size - s.length();
        for(int i = 0; i < s.length()；i++) {
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
int main() {
    cout<<endl;
    return 0;
}
