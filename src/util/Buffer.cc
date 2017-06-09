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
//************ uint8_t uint16_t uint32_t uint64_t array *************//
  template<typename T>
  void write(T v[], size_t n) {
        checArraySpace(v,n);
    for (size_t i = 0; i < n; i++) {
        *(T*)p = v[i];
        p += sizeof(T);
    }
    availSize -= n * sizeof(T);
  }

//*********************************//
//************ uint8_t uint16_t uint32_t uint64_t vector *************//
    void write(const vector<T> & v) {
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
  void checkWriteMeta(uint32_t[] v, size_t n) {
    Type tag = n < 256 ? LIST1 : (n < 65536 ? LIST2 : LIST4);
    *p++ = tag;

  }
//*********************************//
//************ string **************//`
//*******************************//
  void write(string s1) {
    for(uint8_t i = 0; i < s.length();i++) {
            *(T *)p = s[i];
            p += sizeof(T);
    }
    availSize -= s.length() * sizeof(T);
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
