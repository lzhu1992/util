#ifndef CONFIG_HH_
#define CONFIG_HH_

#include <string>
#include <fstream>
#include <map>
#include <regex>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

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


int stringToInt(string s) {
	//Program to convert the strings to integers
	int x = 0;
	for (int i = 0; i < s.length(); i++) {
		x = x * 10 + int(s[i]);
	}

class BadType { 
private:
	const string filename;
	int lineNum;
public:
	BadType(const char filename[], int lineNum) : lineNum(lineNum), filename(filename) {}
	friend ostream& operator <<(ostream& s, constBadType& e) {
		return s<<"Bad Type at " << e.filename << ": " << e.lineNum;
	}
};

class Config {
private:
	
	class memsize{
		//class for defining meory of type 50M, for 50MB where size is 50, 
		//and the multiplier is for M where we can use it to make it 10^6
	public:
		int size;
		char mul; //multiplier
		memsize(int s, char m;){ size = s;  mul = m; }
		//To print it for debuggng purposes
		friend std::ostream& operator <<(std::ostream& s, memsize a) {
			return s << a.size << a.mul; 
		}
		~memsize() { delete size; delete mul; }
	};

	class LogLevel{}; //ToDo: Write this


	struct Sym {
		enum Type {U32, U64, I32, I64, D, S, B, SH, VEC, BUFFER, LL};

		typedef void (*ConversionFunc)(const string &a, Sym *s); //

		static ConversionFunc converters[] = {convertToI32, }; 

		Type type;
		union {
			uint32_t u32;
			uint64_t u64;
			int32_t  i32;
			int64_t  i64;
			double   d;
			string   s;
			boolean	 b;
			shape    sh; //ToDo: write shape in the relevant header
			vec3D    vec; //ToDo: check spelling of vec3D when we incldue the header
			memsize  buffer;
			LogLevel ll; //ToDo: write log level
		};

		Sym(uint32_t u32) : type(U32),  u32(u32) {}
		Sym(uint64_t u64) : type(U64),  u64(u64) {}
		Sym(int32_t i32)  : type(I32),  i32(i32) {}
		Sym(int64_t i64)  : type(I64),  i64(i64) {}
		Sym(double d) 	  : type(D),    d(d) {}
		Sym(string s)	  : type(S),    s(s) {}
		Sym(boolean b)	  : type(B),    b(b) {}
		Sym(shape sh) 	  : type(SH),   sh(sh) {}
		Sym(vec3D vec) 	  : type(VEC),  vec(vec) {}
		Sym(memsize buff)  : type(BUFFER), buffer(buffer) {}
		Sym(LogLevel ll)  : type(LL),   ll(ll){}

	};

	std::map<string, Sym*> fields;


public:
	
	Config(const char filename[], ...);
	void load(const char filename[], ...);
	void save(const char filename[]);
	// TODO: Find out C++ syntax to have one name get<type>
	// TODO: Check if "const char name[]" is needed in the parameter
	/*
	uint8_t getUInt8(const char name[]) const;
	uint16_t getUInt16(const char name[]) const;
	uint32_t getUInt32(const char name[]) const;
	uint64_t getUInt64(const char name[]) const;
	//TODO:	template<typename T>
	//	get<T>(const char name[]) {
	double getDouble(const char name[]) const;
	string getString(const char name[]) const;
	vector<uint32_t> getVector(const char name[]) const; */

	//TODO: create BadType exception

	uint32_t getUInt32() const { 
		if (type != U32)
			throw BadType(__FILE__, __LINE__);
		return u32;
	}
	uint64_t getUInt64() const { 
		if (type != U64)
			throw BadType(__FILE__, __LINE__);
		return u64;
	}
	int32_t getInt32() const { 
		if (type != I32)
			throw BadType(__FILE__, __LINE__);
		return i32;
	}

	int64_t getInt64() const { 
		if (type != I64)
			throw BadType(__FILE__, __LINE__);
		return i64;
	}
	double getDouble() const {
		if (type != D) {
			throw BadType(__FILE__, __LINE__);
		}
		return d;
	}
	string getString() const {
		if (type != S) {
			throw BadType(__FILE__, __LINE__);
		}
		return s;
	}
	boolean getBoolean() const {
		if (type != B) {
			throw BadType(__FILE__, __LINE__);
		}
		return b;
	}
	shape getShape() const {
		if (type != SH) {
			throw BadType(__FILE__, __LINE__);
		}
		return sh;
	}
	vec3D getVec3D() const {
		if (type != VEC) {
			throw BadType(__FILE__, __LINE__);
		}
		return vec;
	}
	memsize getBuffer() const {
		if (type != BUFFER) {
			throw BadType(__FILE__, __LINE__);
		}
		return buff;
	}
	LogLevel getLogLevel() {
		if (type != LL) {
			throw BadType(__FILE__, __LINE__);
		}
		return ll;
<<<<<<< HEAD
	}	
=======
	}
>>>>>>> 3d4f71bd9eac893eeb2ed4df15127be1dc0a1568

	// set the value so that when config file is written, it is updated
	void set(const char name[], double val) {
		fields.set(name, new Sym(D, val));
	}

	static void convertToI32(const string s, Sym* sym){
		sym.i32=stoi(s);
	}

	void filereader(string name){
	//Should this function return a map instead?

		//Function to read the config file and update it to the hashmap for the configuration
		string line, key, val;
		int flag;
		regex comment ("#.*$");
		regex whitespace ("^ +| +$|( ) +|\\t+");
		ifstream reader;
		reader.open(name, ios::in);
		while(!reader.eof()){
			getline(reader, line);
			//removing the comments
			line = regex_replace(line, comment, "");
			//removing whitespaces
			line = regex_replace(line, whitespace, "");
			//If the line is empty, continue
			if(line=="")
				continue;
			// split comment-less line into tokens and see how we add them to the map.
			char_separator<char> sep(", ");
			flag=0;
			tokenizer< char_separator<char> > tokens(line, sep);
			for (const auto& t : tokens){
				if (flag==0){
					flag++;
					key = t;
				}
				else
					val = t;
			}
			fields[key]=val;
		    //TODO: change this from string to the type of data we need
		}
		reader.close();
	}
};

#endif
