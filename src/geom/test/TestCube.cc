#include "../Vec3d.hh"
using namespace std;
using namespace geom;
#define print(v) cout << #v << ' ' << v << '\n'

/*
  Test all operations for Cube
*/
int main() {
  const Cube c1(0, 0, 0, 9);              print(c1);
  const Cube c2(0, 0, 0, 9, 9, 9);        print(c2);
  const Cube c3(0, 0, 0, 7, 7, 7);        print(c3);
  double d1 = c1.volume();                print(d1);
  double d2 = c1.area();                  print(d2);
  double d3 = c2.volume();                print(d1);
  double d4 = c2.area();                  print(d2);
  double d5 = c3.volume();                print(d1);
  double d6 = c3.area();                  print(d2);
}
