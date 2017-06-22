#include "util/Benchmark.hh"
#include <unistd.h>
using namespace std;

Benchmark::Benchmark() :
  elapsedUserTime(0), elapsedSystemTime(0), elapsedWallTime(0),
  BENCHCLOCKS_PER_SEC(sysconf(_SC_CLK_TCK)) {
}


void Benchmark::start() {
  times(&startCPUTimes);
  time(&startWallTime);
}

void Benchmark::stop() {
  struct tms endCPUTimes;
  time_t endWallTime;
  times(&endCPUTimes);
  time(&endWallTime);
  elapsedUserTime += endCPUTimes.tms_utime - startCPUTimes.tms_utime;
  elapsedSystemTime += endCPUTimes.tms_stime - startCPUTimes.tms_stime;
  elapsedWallTime += endWallTime - startWallTime;
}

void Benchmark:: benchmark(void (*Func)() ) {


}





ostream& operator <<(ostream& s, const Benchmark& b) {
  return
    s <<
    "User:   " << b.elapsedUserTime / double(b.BENCHCLOCKS_PER_SEC) << '\n' <<
    "System: " << b.elapsedSystemTime  / double(b.BENCHCLOCKS_PER_SEC) << '\n' <<
    "Wall:   " << b.elapsedWallTime << '\n';
}
