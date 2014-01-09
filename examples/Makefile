CFLAGS  = -W -Wall -I.. -pthread -g -pipe $(COPT)
DLL_FLAGS = -DLUA_COMPAT_ALL -I../build

ifeq ($(OS),Windows_NT)
else
  UNAME_S := $(shell uname -s)
  DLL_FLAGS += -shared

  ifeq ($(UNAME_S),Linux)
    CFLAGS += -ldl
  endif

  ifeq ($(UNAME_S),Darwin)
    #  DLL_FLAGS += -bundle -undefined dynamic_lookup -dynamiclib
    DLL_FLAGS += -flat_namespace -undefined suppress -dynamiclib
  endif
endif

all:
	$(CC) wechat.c ../mongoose.c  -o wechat $(CFLAGS)


MSVC    = ../../vc6
CL      = $(MSVC)/bin/cl
CLFLAGS = /MD /TC /nologo $(DBG) /W3 /DNO_SSL \
        /I$(MSVC)/include /I.. /Dsnprintf=_snprintf
LFLAGS  = /link /incremental:no /libpath:$(MSVC)/lib /machine:IX86

windows:
	$(CL) wechat.c ../mongoose.c $(CLFLAGS) $(LFLAGS)

clean:
	rm -rf wechat *.exe *.dSYM *.obj .*o
