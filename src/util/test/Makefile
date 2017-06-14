INC	:= -I ../..
include	../../../Makefile.inc

all: TestConfig TestBuffer TestLog

clean:
	rm *.o

TestConfigObj	:= TestConfig.o Config.o
TestConfig: $(TestConfigObj)
	$(CXX) $(LDFLAGS) $(TestConfigObj) -o TestConfig

TestConfig.o: TestConfig.cc ../Config.hh
	$(CXX) $(CFLAGS) -c $<

Config.o: ../Config.cc
	$(CXX) $(CFLAGS) -c $<


TestBufferObj	:= TestBuffer.o Buffer.o
TestBuffer: $(TestBufferObj)
	$(CXX) $(LDFLAGS) $(TestBufferObj) -o TestBuffer

TestBuffer.o: TestBuffer.cc Buffer.o ../Buffer.hh
	$(CXX) $(CFLAGS) $<

Buffer.o: ../Buffer.cc ../Buffer.hh
	$(CXX) $(CFLAGS) $<

TestLog: Log.o

Log.o:	../Log.cc
	$(CXX) $(CFLAGS) $<	
