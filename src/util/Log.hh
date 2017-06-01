#ifndef LOG_HH_
#define LOG_HH_
#include <unistd.h>

class Log {
private:
	Level threshhold;
	int fh;
public:
	Log(const char filename[]);
	~Log() { close(fh); }
	enum Level { INFO, DEBUG, WARNING, ERROR, CRITICAL };
	void setLevel(Level level) {
		threshhold = level; // ignore all logging message < this level
	}
	void log(Level severity, uint16_t message) {}
	void log(Level severity, uint16_t message, uint32_t param) {}
	void log(Level severity, uint16_t message, uint32_t param1, uint32_t param2) {}
	// write a variable-length string into the log, pad to 32-bit length
	void log(Level severity, uint16_t message, const string& name) {}
	void warn(uint16_t message) {
		log(WARN, message);
	}
	void error(uint16_t message) {
		log(ERROR, message);
	}
	void critical(uint16_t message) {
		log(CRITICAL, message);
	}
};

/**


 */
class LogReader {
public:
	LogReader(const char filename[], const char language[]);
	bool hasNext(){}
	bool hasNext(Level severity) {}
	bool hasNext(uint16_t message) {}

	//print the current message
	void print(ostream& s);
};
#endif
