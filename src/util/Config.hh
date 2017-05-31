#ifndef CONFIG_HH_
#define CONFIG_HH_

#include <cstdint>
#include <string>
#include <fstream>
#include <map>
#include <regex>
#include <boost/tokenizer.hpp>
#include "util/Vec3d.hh"

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

//TODO: Kill if this is no longer used
int stringToInt(string s) {
	//Program to convert the strings to integers
	int x = 0;
	for (int i = 0; i < s.length(); i++) {
		x = x * 10 + int(s[i]);
	}

//TODO: Insert comment describing BadType

class BadType { 
private:
	const string filename;
	int lineNum;
public:
	BadType(const char filename[], int lineNum) : lineNum(lineNum), filename(filename) {}
	friend ostream& operator <<(ostream& s, const BadType& e) {
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
		memsize(int s, char m) { size = s;  mul = m; }
		//To print it for debuggng purposes
		friend std::ostream& operator <<(std::ostream& s, memsize a) {
			return s << a.size << a.mul; 
		}
		~memsize() { delete size; delete mul; }//TODO: eliminate delete! no memory used
	};

	class LogLevel{}; //ToDo: Write this
	
	struct Sym {
		enum Type {U32, U64, I32, I64, D, S, B, SH, VEC, BUFFER, LL};

		typedef void (*ConversionFunc)(const string &a, Sym *s); // this typedef is to
		// make all the conversion function pointers. 

		static const ConversionFunc converters[] = {convertToUI32, convertToUI64,
		convertToI32, convertToI64, convertToD, convertToB, convertToSH,
		convertToVEC, convertToBUFFER, convertToLL}; //this array will contain all the 
		// function names so that we can retrieve the function in O(1) time
		// It is an array of function pointers.

		Type type;
		union {
			uint32_t u32;
			uint64_t u64;
			int32_t  i32;
			int64_t  i64;
			double   d;
			string   s;
			bool	 b;
			shape    sh; //ToDo: write shape in the relevant header
			vec3D    vec; //ToDo: check spelling of vec3D when we incldue the header
			memsize  buffer;
			LogLevel ll; //ToDo: write log level
		};

		//Constructors
		Sym(uint32_t u32) : type(U32),  u32(u32) {}
		Sym(uint64_t u64) : type(U64),  u64(u64) {}
		Sym(int32_t i32)  : type(I32),  i32(i32) {}
		Sym(int64_t i64)  : type(I64),  i64(i64) {}
		Sym(double d) 	  : type(D),    d(d) {}
		Sym(string s)	  : type(S),    s(s) {}
		Sym(boolean b)	  : type(B),    b(b) {}		// "true" = true = 1, "false" = false = 0
		Sym(shape sh) 	  : type(SH),   sh(sh) {}	// TODO: later
		Sym(const Vec3d& vec) 	  : type(VEC),  vec(vec) {}	// [1.0,1.0,1.0]
		Sym(memsize buff) : type(BUFFER), buffer(buffer) {}		// int and a char
		Sym(LogLevel ll)  : type(LL),   ll(ll){}	// TODO: later

	};
	static void convertToUI32(const string& s, Sym* sym){
		sym.u32=stoul(s);
	}
	static void convertToUI64(const string& s, Sym* sym){
		sym.u64=stoul(s);
	}
	static void convertToI32(const string& s, Sym* sym){
		sym.i32=stoi(s);
	}
	static void convertToI64(const string& s, Sym* sym){
		sym.i64=stoi(s);
	}
	static void convertToD(const string& s, Sym* sym) {
		sym.d=stod(s);
	}
	static void convertToB(const string& s, Sym* sym) {
		if (s.compare("true") == 0) {
			sym.b=1;
		}
		else {
			sym.b=0;
		}
	}
	static void convertToSH(const string& s, Sym* sym) {		// TODO: get the constructor
		
	}
	static void convertToVEC(const string& s, Sym* sym) {
		int i = 0;
		int flag = 0;
		int mul = 10;
		double a = 0;
		double d[3];
		for (int j = 0; j < s.length(); j++) {
			if (s[j]==(',')) {
				d[i] = a;
				a = 0;
				mul = 10;
				flag = 0;
				i++;
			}
			else if (s[j]==('.')){
				flag = 1;
				mul = 10;
			}
			else if (flag == 0) {
				a = a * 10 + double(s[j]) - 48;
			}
			else if (flag == 1) {
				a = a + ((double(s[j])) - 48)/mul;
				mul*=10;
			}
		}
		sym.vec=vec3d(d[0],d[1],d[2]);
		//VEC3D CONSTRUCTOR: Vec3d(double x, double y, double z)
	}
	static void convertToBUFFER(const string& s, Sym* sym) {
		char mult = s.end();
		s.assign(s.begin(), s.end()-1); //Removing the last character
		sym.buffer = buffer(stoi(s);, mult);
	}
	static void convertToLL(const string& s, Sym* sym) {
		
	}

	
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

	template <typename T>
		T get<T>(Type t) const {
			if (type != T) {
				throw BadType(__FILE__,__LINE__);
			}
			return union.t;
		}

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
	}

	// set the value so that when config file is written, it is updated
	void set(const char name[], double val) {
		fields.set(name, new Sym(D, val));
	}



	void filereader(string name){
	//Should this function return a map instead?

		//Function to read the config file and update it to the hashmap for the configuration
		string line, key, val;
		int flag;
		regex comment ("#.*$");
		regex whitespace ("^ +| +$|( ) +|\\t+");
		regex checkVector("(\[\d+(.\d*),\d+(.\d*),\d+(.\d*)\])"); //this reads vector in form of [double,double,double]
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
