#ifndef LOG_HH_
#define LOG_HH_

#include <cstdint>
#include <string>
#include <unistd.h>
#include <fcntl.h>

class Log {
public:
	enum Level { INFO, DEBUG, WARN, ERROR, CRITICAL };
private:
	Level lev;
	int fh;
public:
	Log() {}
	~Log() {
		if (fh >= 0)
			close(fh);
	}


	void setLogFile(const char filename[]) {
		fh = creat(filename, 0644);
		if (fh < 0)
			throw "IOEXception"; // TODO: Put in real exception object!
	}

	void setLevel(Level L) {
		lev = L;
	}
	void log(Level severity, uint16_t message) {}
	void log(Level severity, uint16_t message, uint32_t param) {}
	void log(Level severity, uint16_t message, uint32_t param1, uint32_t param2) {}
	// write a variable-length string into the log, pad to 32-bit length
	void log(Level severity, uint16_t message, const std::string& name) {}
	void warn(Errcode message) {
		log(Level::WARN, (uint16_t)message);
	}
	void error(Errcode message) {
		log(Level::ERROR, (uint16_t)message);
	}
	void critical(Errcode message) {
		log(Level::CRITICAL, (uint16_t)message);
	}
};

/**
	 Display a binary log in a user's preferred language
 */
class LogReader {
public:
	LogReader(const char filename[], const char language[]);
	//TODO: Fix these next two functions
	bool hasNext(Log::Level severity) { return false; }
	bool hasNext(uint16_t message) { return false; }

	//print the current message
	void print(std::ostream& s);
};
#endif
