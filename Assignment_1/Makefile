rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
src := $(call rwildcard,./,*.cpp)

obj = $(patsubst %.cpp,%.o,$(src))

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 

INTELMAC_INCLUDE=-I/usr/local/include							# Intel  Silicon Ubuntu VM
UBUNTU_INTEL_INCLUDE=-I/usr/include 							# Intel Ubuntu VM	
UBUNTU_INTEL_LIB=-L/usr/lib/x86_64-linux-gnu					# Intel Ubuntu VM
UBUNTU_INTEL_INCLUDE=-I/usr/include 							# Intel 


UBUNTU_COMPILER=/usr/bin/g++

all: MonsterArena
uname_s := $(shell uname -s)
MonsterArena : MonsterArena.o
ifeq ($(uname_s),Linux)
	$(UBUNTU_COMPILER) -std=c++17 -o $@ $^ $(LDFLAGS)-L/usr/lib/aarch64-linux-gnu
endif

uname_s := $(shell uname -s)
MonsterArena.o: MonsterArena.cpp
ifeq ($(uname_s),Linux)
	$(UBUNTU_COMPILER) -std=c++17 -c $^ -o $@ $(UBUNTU_INTEL_INCLUDE)
endif

.PHONY: clean
clean:
	rm -f $(obj) MonsterArena
	