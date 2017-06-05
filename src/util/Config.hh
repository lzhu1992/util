#ifndef CONFIG_HH_
#define CONFIG_HH_

#include <cstdint>
#include <cstdarg>
#include <string>
#include <fstream>
#include <map>
#include <regex>
//#include <boost/any.hpp>
#include "geom/Vec3d.hh"

using namespace std;
using namespace geom;
//using namespace boost;

/**
	 Represent a config file used to configure complicated applications

	 File format supports comments starting with #
	 name-value pairs of data, with declaration of the type of names supported
	 in the constructor so that subclsses of Config can specify the required 
	 types of each tag.  In this way, the Config utility can display the
	 line number and an error if the data is not as required

	 TODO: Since Config files can be very large, and parsing is slow, it is
	 possible to extend this model to automatically generate a binary version 
	 of the config.  In this way, the config file can effectively be compiled.
	 This is important only if the file is large so at the moment we can ignore
 */

class BadType { //BadType exception is thrown when an incorrect type is passed as a parameter for the "get" functions
	private:
		const string filename;
		int lineNum;
	public:
		BadType(const char filename[], int lineNum) :
			lineNum(lineNum), filename(filename) {}
		friend ostream& operator <<(ostream& s, const BadType& e) {
			return s << "Bad Type at " << e.filename << ": " << e.lineNum;
		}
};

class Config {
public:
	enum Type {UINT16, UINT32, UINT64, INT16, INT32, INT64,
						 DOUBLE, STRING, BOOL};
private:
	struct Sym {
		Type type;
		union {
			uint16_t u16;
			uint32_t u32;
			uint64_t u64;
			int16_t  i16;
			int32_t  i32;
			int64_t  i64;
			double   d;
			string   *s;
			bool	   b;
		};

		//Constructors
		Sym(uint16_t u16) : type(UINT16),  u32(u32) {}
		Sym(uint32_t u32) : type(UINT32),  u32(u32) {}
		Sym(uint64_t u64) : type(UINT64),  u64(u64) {}
		Sym(int32_t i32)  : type(INT32),   i32(i32) {}
		Sym(int64_t i64)  : type(INT64),   i64(i64) {}
		Sym(double d) 	  : type(DOUBLE),  d(d)     {}
		Sym(const string& str)	: type(STRING),  s(new string(str))   {}
		Sym(bool b)	      : type(BOOL),    b(b)     {}// true = 1, false = 0
		Sym(double size, char mul) : type(UINT64) { // 1024 or 128k or 16M or 2G
			if (mul == 'k') size *= 1024;
			if (mul == 'M') size *= 1024*1024;
			if (mul == 'G') size *= 1024*1024*1024;
			u64 = uint64_t(size);
		}
		~Sym() {
			switch(type) {
			case STRING: delete [] s; break;
			}
		}
	};
	std::map<string, Type> types;
	std::map<string, Type> optTypes;
	std::map<string, Sym> f;

	const static regex commentOrWhitespace;
	const static regex checkVector;
	
	const Sym* getSym(const string& name, int linenum) const {
		map<string,Sym>::const_iterator i = f.find(name);
		if (i == f.end())
			throw BadType(__FILE__, linenum);
		return &i->second;
	}
public:	
	Config(){}
	void load(const string& filename);
	void save(const string& filename);

	template<typename T>
	void set(const string& name, T val) {
		map<string,Sym>::iterator i = f.find(name);
		if (i == f.end())
			return;
		i->first = name;
		i->second = Sym(val);
	}

	uint16_t getUInt16 (const string& name) const {
		return getSym(name, __LINE__)->u16;
	}

	uint32_t getUInt32 (const string& name) const {
		return getSym(name, __LINE__)->u32;
	}

	uint64_t getUInt64 (const string& name) const {
		return getSym(name, __LINE__)->u64;
	}

	int16_t getInt16 (const string& name) const {
		return getSym(name, __LINE__)->i16;
	}

	int32_t getInt32 (const string& name) const {
		return getSym(name, __LINE__)->i32;
	}

	int64_t getInt64 (const string& name) const {
		return getSym(name, __LINE__)->i64;
	}

	bool getBool(const string& name) const {
		return getSym(name, __LINE__)->b;
	}

	double getDouble (const string& name) const {
		return getSym(name, __LINE__)->d;
	}

	string getString(const string& name) const {
		return *getSym(name, __LINE__)->s;
	}
	void mandatory(int count...);
	void optional(int count...);
};
#endif
