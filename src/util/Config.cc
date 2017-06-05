#include "util/Config.hh"

void Config::save(const string& filename) {
	cout << "Saving Config to " << filename << '\n';
}

const regex Config::commentOrWhitespace("#.*$|^\\s*$");

//this reads vector in form of [double,double,double]
const regex Config::checkVector(R"(\[\d+(.\d*),\d+(.\d*),\d+(.\d*)\])");

void Config::load(const string& name) {
	//Should this function return a map instead?
	//TODO: Change the hashmap allocator at the end of this function
	//Function to read the config file and update it to the hashmap for the configuration
	string line, key, val;
	int flag;
	ifstream reader;
		reader.open(name, ios::in);
		while(!reader.eof()){
			getline(reader, line);
			//removing the comments and blank lines
			line = regex_replace(line, commentOrWhitespace, "");
			//If the line is empty, continue
			if (line=="")
				continue;
			int sep = line.find('\t'); //TODO: use regex to parse
			string name = line.substr(0, sep);
			string val = line.substr(sep+1);
			if (types.find(name) != types.end()) {
			  Type t = types[name];
				cout << t << ": " << val << '\n';
			}
		}
		reader.close();
}

/*
	Define fields that are mandatory in the config file,
	and what types they must be
*/
void Config::mandatory(int count...) {
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; i++) {
		string str = va_arg(args, string);
		Type m = (Type)va_arg(args, int);
		types[str] = m;
	}
	va_end(args);
}

void Config::optional(int count...) {
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; i++) {
		string str = va_arg(args, string);
		Type m = (Type)va_arg(args, int);
		optTypes[str] = m;
	}
	va_end(args);
}
