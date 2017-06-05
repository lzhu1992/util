#ifndef EX_HH_
#define EX_HH_

#include <cstdint>
#include "util/Log.hh"
/*
	Represent an exception class that outputs a numeric error code into
	a binary stream.

	Be sure ErrCode is defined for your application
*/
class Ex {
public:
	const char* filename;
	const uint32_t lineNum;
	Errcode e;
public:
	Ex(const char filename[], uint32_t lineNum, Errcode e) :
		filename(filename), lineNum(lineNum), e(e) {}
};

class FatalEx : public Ex {
private:
public:
	FatalEx(const char filename[], int lineNum, Errcode e) :
		Ex(filename, lineNum, e) {}
};

#endif

