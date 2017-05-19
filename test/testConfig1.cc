#include "Config.hh"

int main() {
  Config c("x.conf",
					 "x", Config::Double,
					 "y", Config::Double,
					 "z", Config::Double);

  cout << c.get<double>("x") << '\n';
  cout << c.get<double>("y") << '\n';
	cout << c.get<double>("z") << '\n';
}
