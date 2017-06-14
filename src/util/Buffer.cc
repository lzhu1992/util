//
// Created by Xiaoxue Guo on 6/14/17.
//

/*
 * Buffer.cpp
 *
 *  Created on: March 22, 2015
 *      Author: Dov Kruger
 */

/*
 * Buffer.cpp
 *
 *  Created on: March 22, 2015
 *      Author: Dov Kruger
 */
#include <cstring>
#include <vector>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "Buffer.hh"
#include "Datatype.h"
using namespace std;

Buffer::Buffer(const char filename[], size_t initialSize) : size(initialSize) {
    buffer = new char[size];
    availSize = size;
    p = buffer;
    fd = creat(filename, O_WRONLY);
    if (fd < 0)
        throw "File cannot write";
}
Buffer::Buffer(const char filename[], size_t initialSize, char*)  : size(initialSize)  {
    buffer = new char[size];
    availSize = size;
    p = buffer;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        throw "File cannot open";
}

void Buffer::readNext() {
    availSize = ::read(fd, buffer, size);
}
void Buffer:: flush () {
    ::write(fd, buffer,p-buffer);
    p = buffer;
    availSize = size;
}

#if 0
//*********************************//
//************ uint8_t uint16_t uint32_t uint64_t array *************//
template<typename T>
void Buffer::write(T v[], size_t n) {
    checArraySpace(v,n);
    for (size_t i = 0; i < n; i++) {
        *(T*)p = v[i];
        p += sizeof(T);
    }
    availSize -= n * sizeof(T);
}


//*********************************//
//************ uint8_t uint16_t uint32_t uint64_t vector *************//
template<typename T>
void Buffer::write(const vector<T>& v) {
    checkVectorSpace(v);
    for (size_t i = 0; i < v.size(); i++) {
        *(T*)p = v[i];
        p += sizeof(T);
    }
    availSize -= v.size() * sizeof(T);
}

//*********************************//
//************ list1 *************//
//************ list2  *************//
//************ list3 *************//
//************ list4 *************//
void checkWriteMeta(uint32_t[]v, size_t n) {
    DataType tag = n < 256 ? LIST1 : (n < 65536 ? LIST2 : LIST4);
    *p++ = tag;

}
//*********************************//
//************ string **************//`
//*******************************//
void Buffer::write(string s) {
    for(uint8_t i = 0; i < s.length();i++) {
        *p++ = s[i];
    }
    availSize -= s.length();
}
//*********************************//
//************** append *******************//
//*********************************//
//*********************************//
#endif
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
	memcp\
  y(buf, "\r\n\r\n", 4);
  length = buf - data;
}

#endif

//read array
/*
template<typename T>
vector<T> readarray<T>() {
    T length = *(*T) p;
    p += sizeof(T);
    vector<T>  *v;
    for (size_t i = 0; i < length; i++) {
        v[i] = *(T*)p = ;
        p += sizeof(T);
    }
    return v;
}
*/
//read string
/*
string readstring1() {
    unit_8 len = *(*unit_8)p;
    p += sizeof(unit_8);
    string s;
    for (size_t i = 0 ; i < length; i++){
        s[i] = *(uint8_t *)p;
        p += sizeof(unit_8);
    }
    return s;
}
string readstring2() {
    unit_16 length = *(*unit_16)p;
    p += sizeof(unit_16);
    string s;
    for (size_t i = 0 ; i < length; i++){
        s[i] = *(uint16_t *)p;
        p += sizeof(unit_16);
    }
    return s;
}
string readstring3() {
    unit_32 length = *(*unit_32)p;
    p += sizeof(unit_32);
    string s;
    for (size_t i = 0 ; i < length; i++){
        s[i] = *(uint32_t *)p;
        p += sizeof(unit_32);
    }
    return s;
}


void Buffer::append(double v[],int number,const std::string& sep){
    checkSpace(number*(20+sep.length()));
    for (int i = 0;i < number-1;i++){
        length += sprintf(data+length,"%lf%s",v[i],sep.c_str());
    }
}
};
 */