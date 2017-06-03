#ifndef LOG_HH_
#define LOG_HH_

#include <cstdint>
#include <string>
class Log {
public:
	enum class Level { INFO, DEBUG, WARN, ERROR, CRITICAL };
private:
	Level lev;
public:
	Log();
	void setLogFile(const char filename[]);
	void setLevel(Level L) {
		lev = L;
	}
	void log(Level severity, uint16_t message) {}
	void log(Level severity, uint16_t message, uint32_t param) {}
	void log(Level severity, uint16_t message, uint32_t param1, uint32_t param2) {}
	// write a variable-length string into the log, pad to 32-bit length
	void log(Level severity, uint16_t message, const std::string& name) {}
	void warn(uint16_t message) {
		log(Level::WARN, message);
	}
	void error(uint16_t message) {
		log(Level::ERROR, message);
	}
	void critical(uint16_t message) {
		log(Level::CRITICAL, message);
	}
};

/**
	 Display a binary log in a user's preferred language
 */
class LogReader {
public:
	LogReader(const char filename[], const char language[]);
	bool hasNext(Log::Level severity) {}
	bool hasNext(uint16_t message) {}

	//print the current message
	void print(std::ostream& s);
};
#endif
