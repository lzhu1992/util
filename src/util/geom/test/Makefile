CXX	:=  g++
DEBUG	:=  -g
OPT	:=  #-O2
CFLAGS	:=  $(DEBUG) $(OPT) -I ../..

OBJ :=	TestPlane TestVec3d TestSphere TestCube
all:  $(OBJ)

TestPlane:  TestPlane.cc
	$(CXX) $(CFLAGS) $< -o TestPlane

TestVec3d:  TestVec3d.cc
	$(CXX) $(CFLAGS) $< -o TestVec3d
	
TestVec3d:  TestSphere.cc
	$(CXX) $(CFLAGS) $< -o TestSphere

TestVec3d:  TestCube.cc
	$(CXX) $(CFLAGS) $< -o TestCube
	