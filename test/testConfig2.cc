#include "Config.hh"

int main() {
	Config c("test.conf",
					 "x", Config::DOUBLE,
					 "y", Config::DOUBLE,
					 "z", Config::DOUBLE,
					 "i32", Config::I32,
					 "u32", Config::U32,
					 "u64", Config::U64,
					 "v", Config::Vec3D,
					 "lst32", Config::ListUINT32,
					 "s", Config::String);

  cout << c.get<double>("x") << '\n';
  cout << c.get<double>("y") << '\n';
	cout << c.get<double>("z") << '\n';
	cout << c.get<double>("i32") << '\n';
	cout << c.get<double>("u32") << '\n';
	cout << c.get<double>("u64") << '\n';
	vector<uint32_t> list = c.get< < vector<uint32_t> >("lst32");
	for (auto x : list) { cout << x << ", "; } cout << '\n';
}
