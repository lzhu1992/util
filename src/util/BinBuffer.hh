/**
	 A binary high-speed buffer to support writing objects portably to a
	 binary stream so it can be read back in (persistence)

 */
class Buffer {
 void Buffer(int initialSize) {
        data = new char[initialSize];
        data[0] = 0;
        size = initialSize;
        length = 0;
        typedef char int8_t;
        typedef signed char int8_t;
        typedef short int16_t;
        typedef int   int32_t;
        typedef unsigned char     uint8_t;
        typedef unsigned short    uint16_t;
        typedef unsigned int      uint32_t;
    }
};
