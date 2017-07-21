#include"BufferPlus.h"
#include<cassert>
void test4() {
    Buffer2 buf("test2.dat", 32);
    uint8_t  a = 1;
    uint16_t b = 2;
    uint32_t c = 257; // 1 in first and second byte low-endian
    uint64_t d = 1024 + 1024*1024 + 1024*1024*1024;
    string e = "abcd";
    buf << a;
    for (uint32_t i = 0; i < 20; i++)
        buf << i;
    buf << b << c << d << e; // 2 + 4 + 8 + 5 bytes for string
    // assert(buf.getTotalBytesSent() == 100);
}
void test5() {
    Buffer2 buf("test2.dat", 32, "IN");
    uint8_t a = buf.readUint8();
    uint32_t v;
    for (int i = 0; i < 20; i++)
        v = buf.readUint32();
    uint16_t b = buf.readUint16();
    uint32_t c = buf.readUint32();
    uint64_t d = buf.readUint64();
    string e = buf.readstring1();
    assert(a == 1);
    assert(b == 2);
    assert(c == 257);
    assert(d == 1024 + 1024 * 1024 + 1024 * 1024 * 1024);
    assert(e == "abcd");
}


int main() {
    test4();
    return 0;
}