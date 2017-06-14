#include "Buffer.hh"
#include <cassert>
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
    Buffer buf("test1.dat",32768,"IN");
    uint8_t  a = buf.readUint8();
    uint16_t b = buf.readUint16();
    uint32_t c = buf.readUint32();
    uint64_t d = buf.readUint64();
//    string e = buf.readString1();
    assert(a == 1);
    assert(b == 2);
    assert(c == 257);
    assert(d == 1024 + 1024*1024 + 1024*1024*1024);
//    assert(e == "abcd");
}

int main() {
    test1();
    test2();

    return 0;
}
