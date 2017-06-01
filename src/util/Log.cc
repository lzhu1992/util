#include "Log.hh"

Log::Log(const char filename[]) {
	fh = creat(filename, 0644);
	if (fh < 0)
		throw "IOEXception"; // TODO: Put in real exception object!
}
