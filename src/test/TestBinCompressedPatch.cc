#include "util/BinCompressedPatch.hh"

int main() {
#if 
  BinCompressedPatch bcp("v1");
  bcp.diff("v2");
  bcp.compress();
  bcp.savePatch("p1");
#endif

  // compute difference from v1 to v2, compress, then save as patch p1
  BinCompressedPatch bcp("v1", "v2", "p1");


}
