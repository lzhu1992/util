#ifndef LOG_HH_
#define LOG_HH_

class Log {

public:
	Log(const char filename[]);
	enum class Level { INFO, DEBUG, WARNING, ERROR, CRITICAL };
	void log(Level severity, uint16_t message) {}
	void log(Level severity, uint16_t message, uint32_t param) {}
	void log(Level severity, uint16_t message, uint32_t param1, uint32_t param2) {}
	// write a variable-length string into the log, pad to 32-bit length
	void log(Level severity, uint16_t message, const string& name) {}
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
