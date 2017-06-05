CXX	:=	g++
DEBUG	:=	-g
OPT	:=	#-O2
LDFLAGS	:=	$(DEBUG)
CFLAGS	:=	$(LDFLAGS) $(OPT) $(INC) -c
