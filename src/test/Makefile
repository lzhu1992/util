CXX	:= g++



all: SampleBinary1 SampleBinary2 TestBinCompressedPatch

SampleBinary1: SampleBinary1.cc
	$(CXX) $< -o $@

SampleBinary2: SampleBinary2.cc
	$(CXX) $< -o $@

TestBinCompressedPatch: TestBinCompressedPatch.cc
	$(CXX) $< -I ../../lib/bsdiff-master -I ../../lib/bzip2/  $@ -L ../../lib/bsdiff-master -L ../../lib/bzip2-1.0.6  -lbz2 -lbsdiff 



