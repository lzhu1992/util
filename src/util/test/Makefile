INC	:= -I ../..
include	../../../Makefile.inc

all: TestConfig

clean:
	rm *.o

TestConfigObj	:= TestConfig.o Config.o
TestConfig: $(TestConfigObj)
	$(CXX) $(LDFLAGS) $(TestConfigObj) -o TestConfig

TestConfig.o: TestConfig.cc ../Config.hh
	$(CXX) $(CFLAGS) -c $<

Config.o: ../Config.cc
	$(CXX) $(CFLAGS) -c $<


