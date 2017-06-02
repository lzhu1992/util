#include "../Vec3d.hh"
using namespace std;
using namespace geom;
#define print(v) cout << #v << ' ' << v << '\n'

/*
  Test all operations for Sphere
*/
int main() {
  const Sphere s1(0, 0, 0, 9);            print(s1);
  double d1 = s1.volume();                print(d1);
  double d2 = s1.area();                  print(d2);
  Cube c1 = s1.boundingCube();            print(c1);
}
