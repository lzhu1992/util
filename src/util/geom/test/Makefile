CXX	:=  g++
DEBUG	:=  -g
OPT	:=  #-O2
CFLAGS	:=  $(DEBUG) $(OPT) -I ../..

OBJ :=	TestPlane TestVec3d
all:  $(OBJ)

TestPlane:  TestPlane.cc
	$(CXX) $(CFLAGS) $< -o TestPlane

TestVec3d:  TestVec3d.cc
	$(CXX) $(CFLAGS) $< -o TestVec3d
	