#include "util/Buffer.hh"
/**
	 @author Lin 

 */


/*
describe

 */
void test1() {
	Buffer buf("test1.dat", 32768);
	uint8_t  a = 1;
	uint16_t b = 2;
	uint32_t c = 257; // 1 in first and second byte low-endian
	uint64_t d = 1024 + 1024*1024 + 1024*1024*1024;
	string e = "abcd";
 	buf << a << b << c << d << e; // 1 + 2 + 4 + 8 + 5 bytes for string

}

/*
	describe test here please!

 */

void test2() {

}
int main() {
	test1();
	test2();
	
	return 0;
}
