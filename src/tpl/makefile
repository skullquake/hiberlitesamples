#CC=x86_64-linux-gnu-gcc-9
#CXX=x86_64-linux-gnu-g++-9
#CC=x86_64-w64-mingw32-gcc-posix
#CXX=x86_64-w64-mingw32-g++-posix
CC=x86_64-w64-mingw32-gcc
CXX=x86_64-w64-mingw32-g++
ifeq ($(CC),)
	CC=gcc
endif
ifeq ($(CXX),)
	CXX=g++
endif
SRC=./src/a.c
SRCDIR=./src
COMPILERVERSION=$(shell $(CC) -dumpversion)
TGT_MACHINE=$(shell $(CC) -dumpmachine)
LIBNAM=$(shell basename `pwd`)
CFLAGS+=-Wall
CFLAGS+=-I./src
CFLAGS+=-I./src/SqliteCpp
CFLAGS+=-I./src/hiberlite
CFLAGS+=-I./src/sqlite
ifneq (,$(findstring mingw,$(TGT_MACHINE)))
	LDFLAGS+=-static
	LDFLAGS+=-lpthread
	#customize mingw
	ifneq (,$(findstring posix,$(TGT_MACHINE)))
		#customize mingw posix
	else
		#customize mingw nonposix
	endif
else
	LDFLAGS+=-lpthread
	LDFLAGS+=-ldl
	#customize linux
endif
#set binary extension
ifneq (,$(findstring mingw,$(TGT_MACHINE)))
	BINEXT=.exe
else
	BINEXT=.out
endif
OUTDIR=./bin
BINDIR=$(OUTDIR)/$(TGT_MACHINE)
BIN:=$(BINDIR)/$(LIBNAM)$(BINEXT)
SRC:=$(shell find $(SRCDIR) -name '*.c')
OBJS:=$(addprefix $(BINDIR)/,$(SRC:%.c=%.o))
SRCCPP:=$(shell find $(SRCDIR) -name '*.cpp')
OBJSCPP:=$(addprefix $(BINDIR)/,$(SRCCPP:%.cpp=%.o))
all:$(BIN)
$(BIN):$(OBJS) $(OBJSCPP)
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGS)\
		$(OBJS)\
		$(OBJSCPP)\
		$(LDFLAGS)\
		-o $(BIN)
$(BINDIR)/%.o: %.c
	@printf "generating [c]   $@...\n"
	@mkdir -p $(@D)
	@$(CC)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@
$(BINDIR)/%.o: %.cpp
	@printf "generating [cpp] $@...\n"
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@

.phony:clean lsvar
clean:
	@rm -r ./bin
run:$(BIN)
	$(BIN)
lsvar:
	echo $(SRC)
	echo $(OBJS)
	echo $(SRCCPP)
	echo $(OBJSCPP)

