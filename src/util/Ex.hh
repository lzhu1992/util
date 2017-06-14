#pragma once

#include <cstdint>
#include <iostream>
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
	friend std::ostream& operator <<(std::ostream& s, const Ex& e) {
		return s << e.filename << ": " << e.lineNum << " Errcode=" << int(e.e) << '\n';
	}
};

class FatalEx : public Ex {
private:
public:
	FatalEx(const char filename[], int lineNum, Errcode e) :
		Ex(filename, lineNum, e) {}
};
