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
public:
  Buffer::Buffer(const char filename[], size_t initialSize) : size(initialSize) {
    buffer = new char[size];
    availSize = size;
    p = buffer;
    fd = creat(filename, O_WRONLY);
    if (fd < 0)
        throw "File cannot open";
  }  
//*********************************//
//************ uint8_t array *************//
//************ uint16_t array *************//
//************ uint32_t array *************//
//************ uint64_t array *************//
  void write(uint8_t[] v, size_t n) {
    checkWrite1(v,n);
    for (size_t i = 0; i < n; i++) {
        *(uint8_t*)p = v[i];
        p += sizeof(v);
    }
    availSize -= n * sizeof(v);
  } 
    void write(uint16_t[] v, size_t n) {
      checkWrite2(v,n);
      for (size_t i = 0; i < n; i++) {
        *(uint16_t*)p = v[i];
        p += sizeof(v);
      }
      availSize -= n * sizeof(v);
  }
    void write(uint32_t[] v, size_t n) {
      checkWrite3(v,n);
      for (size_t i = 0; i < n; i++) {
        *(uint32_t*)p = v[i];
        p += sizeof(v);
      }
      availSize -= n * sizeof(v);
  }
    void write(uint64_t[] v, size_t n) {
      checkWrite4(v,n);
      for (size_t i = 0; i < n; i++) {
        *(uint64_t*)p = v[i];
        p += sizeof(v);
     }
     availSize -= n * sizeof(v);
  }
  
//*********************************//
//************ uint8_t vector *************//
//************ uint16_t vector *************//
//************ uint32_t vector *************//
//************ uint64_t vector *************//
 void write(const vector<uint8_t> & v) {
    checkWriteMax1(v);
     *(uint8_t*)p = v;
     for (size_t i = 0; i < v.size(); i++) {
        *(uint8_t*)p = v[i];
        p += sizeof(v);
      }
    availSize -= v.size() * sizeof(v);
  } 
 void write(const vector<uint16_t> & v) {
    checkWriteMax2(v);
    for (size_t i = 0; i < v.size(); i++) {
        *(uint16_t*)p = v[i];
        p += sizeof(v);
      }
    availSize -= v.size() * sizeof(v);
  } 
 void write(const vector<uint32_t> & v) {
    checkWriteMax3(v);
    for (size_t i = 0; i < v.size(); i++) {
        *(uint32_t*)p = v[i];
        p += sizeof(v);
      }
     availSize -= v.size() * sizeof(v);
  } 

  void write(const vector<uint64_t> & v) {
     checkWriteMax4(v);
     for (size_t i = 0; i < v.size(); i++) {
        *(uint64_t*)p = v[i];
        p += sizeof(v);
      }
     availSize -= v.size() * sizeof(v);
  } 
//*********************************//
//************ uint8_t operator *************//
//************ uint16_t operator *************//
//************ uint32_t operator *************//
//************ uint64_t operator *************//
  Buffer& operator <<(uint32_t v) {
    checkSize(sizeof(v));
    write(v);
    return *this;    
  }

  //*********************************//
//************ list1 *************//
//************ list2  *************//
//************ list3 *************//
//************ list4 *************//
  void checkWriteMeta(uint32_t[] v, size_t n) {
    Type tag = n < 256 ? LIST1 : (n < 65536 ? LIST2 : LIST4);
    *p++ = tag;

  }
//*********************************//
//************ string **************//`
//*******************************//
  void write(string s1) {// Do I need to check size
    for(uint8_t i = 0; i < s.length();i++) {
            *(uint8_t *)p = s[i]; 
            p += sizeof(s);
    }
    availSize -= s.length() * sizeof(s);
  }  
    void write(string s2) {// Do I need to check size
    for(uint16_t i = 0; i < s.length();i++) {
            *(uint16_t *)p = s[i]; 
            p += sizeof(s);
    }
    availSize -= s.length() * sizeof(s);
  } 
   void write(string s4) {// Do I need to check size
    for(uint32_t i = 0; i < s.length();i++) {
            *(uint32_t *)p = s[i]; 
            p += sizeof(s);
    }
    availSize -= s.length() * sizeof(s);
  } 
//*********************************//
//************** append *******************//
//*********************************//
//*********************************//

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
};
