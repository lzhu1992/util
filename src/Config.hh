#ifndef CONFIG_HH_
#define CONFIG_HH_

#include <string>
#include <map>
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

class Config {
private:
	struct Sym {
		enum Type {U32, U64, I32, D, S};
		Type type;
		union {
			uint32_t u32;
			uint64_t u64;
			int32_t  i32;
			int64_t  i64;
			double   d;
			string   s;
		};
	};
	class Sym {
	public:
		virtual T getValue() const = 0;
	};
	class UInt32Sym : public Sym {
		uint32_t getValue() const;
	}
	class UInt32Sym : public Sym {
		uint32_t getValue() const;
	}
	class DoubleSym : public Sym {
		double getValue() const;
	}

	std::map<string, Sym*> fields;
public:
	Config(const char filename[], ...);
	void load(const char filename[], ...);
	void save(const char filename[]);
	// TODO: Find out C++ syntax to have one name get<type>
	uint8_t getUInt8(const char name[]) const;
	uint16_t getUInt16(const char name[]) const;
	uint32_t getUInt32(const char name[]) const;
	uint64_t getUInt64(const char name[]) const;
	//TODO:	template<typename T>
	//	get<T>(const char name[]) {
	double getDouble(const char name[]) const;
	string getString(const char name[]) const;
	vector<uint32_t> getVector(const char name[]) const;

	// set the value so that when config file is written, it is updated
	void set(const char name[], double val) {
		fields.set(name, new Sym(D, val));
	}
};
