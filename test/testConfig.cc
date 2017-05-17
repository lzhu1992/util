#include "Config.hh"

int main() {
  Config c("x.conf", "x", Config::Double,
  "y", Config::Double,
  "z", Config::Double);

  cout << x.get<double>("x") << '\n';
  cout << x.get<double>("x") << '\n';
}
