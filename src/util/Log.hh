#ifndef LOG_HH_
#define LOG_HH_

#include <cstdint>
#include <string>
class Log {

public:
	Log();
	void setLogFile(const char filename[]);
	enum class Level { INFO, DEBUG, WARNING, ERROR, CRITICAL };
	void log(Level severity, uint16_t message) {}
	void log(Level severity, uint16_t message, uint32_t param) {}
	void log(Level severity, uint16_t message, uint32_t param1, uint32_t param2) {}
	// write a variable-length string into the log, pad to 32-bit length
	void log(Level severity, uint16_t message, const std::string& name) {}
};

/**
	 Display a binary log in a user's preferred language
 */
class LogReader {
public:
	LogReader(const char filename[], const char language[]);
	bool hasNext(){}
	bool hasNext(Log::Level severity) {}
	bool hasNext(uint16_t message) {}

	//print the current message
	void print(std::ostream& s);
};
#endif