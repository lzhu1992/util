#pragma once
#include <cstdint>
#include <time.h>
#include <iostream>

class Benchmark {
private:
	uint64_t elapsedUserTime, elapsedSystemTime, elapsedWallTime;
	int BENCHCLOCKS_PER_SEC;
	// struct tms startCPUTimes;
	// struct tms startWallTime;
public:
	Benchmark();
	// measure how long it takes to execute a function
	static void benchmark(void (*Func)() );
	uint64_t elapsed() const;
	void start();
	void end();
	friend std::ostream& operator <<(std::ostream& s, const Benchmark& b);
};
