CXX	:=	g++
DEBUG	:=	-g
OPT	:=	#-O2
LDFLAGS	:=	$(DEBUG) $(OPT)
CFLAGS	:=	$(LDFLAGS) $(INC) -c
