CC = g++ -Wall -std=c++20 -fPIC
PLATFORM = linux
PLATVER = 
PLATDIR = 
FILEEXT = 
LIBFLAG = 
RELEASE = 0
UNICODE = 0
LOADHDR = -I ./ -I /usr/include/lua5.4 -I /usr/local/include/lua
LOADSO = 
LIB = -lXEngine_BaseLib
LIBEX = 
OBJECTS = ModulePlugin_LibCore.o ModulePlugin_LuaCore.o ModulePlugin_Loader.o pch.o

MACRO_LUA_SUPPORT := $(shell gcc -E -dM ../XEngine_BuildSwitch.h | grep _XENGINE_BUILD_SWITCH_LUA | cut -d ' ' -f 3)

ifeq ($(RELEASE),1)
FLAGS = -c 
DEBUG = 
else
	ifeq ($(PLATFORM),mac)
		FLAGS = -c
		DEBUG = -g 
	else
		FLAGS = -c -lc_p
		DEBUG = -g -pg 
	endif
endif

ifeq ($(UNICODE),1)
UNICODE = -D _UNICODE
else
UNICODE = 
endif

ifeq ($(PLATFORM),linux)
	ifeq (/etc/redhat-release,$(wildcard /etc/redhat-release))
		PLATVER = -D __CENTOS__
		PLATDIR = XEngine_Linux/Centos
		LIB += -llua
	else
		PLATVER = -D __UBUNTU__
		PLATDIR = XEngine_Linux/Ubuntu
		LIB += -llua5.4
	endif
	FILEEXT = so
	LIBFLAG = -shared
	LIBEX = -lpthread -lrt -ldl
	LOADBIN = -Wl,-rpath=./,--disable-new-dtags
else ifeq ($(PLATFORM),mac)
	CC += -Wno-deprecated-declarations
	PLATVER = -D __MACOS__
	PLATDIR = XEngine_Mac
	FILEEXT = dylib
	LIBFLAG = -dynamiclib

	LOADHDR += -I /opt/homebrew/opt/lua/include/lua
	LOADSO += -L /opt/homebrew/opt/lua/lib

	ifeq ($(MACRO_LUA_SUPPORT),1)
		LIB += -llua
	endif
	LIBEX = -lpthread -ldl
	LOADBIN = -Wl,-rpath,@loader_path/./
endif


all:$(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) -o libXEngine_ModulePlugin.$(FILEEXT) $(LIBFLAG) $(LIB) $(LIBEX) $(LOADSO) $(LOADBIN)

ModulePlugin_LibCore.o:./ModulePlugin_LibCore/ModulePlugin_LibCore.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModulePlugin_LibCore/ModulePlugin_LibCore.cpp
ModulePlugin_LuaCore.o:./ModulePlugin_LuaCore/ModulePlugin_LuaCore.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModulePlugin_LuaCore/ModulePlugin_LuaCore.cpp
ModulePlugin_Loader.o:./ModulePlugin_Loader/ModulePlugin_Loader.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModulePlugin_Loader/ModulePlugin_Loader.cpp 

pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./pch.cpp


InstallAll:InstallSo 
InstallSo:./libXEngine_ModulePlugin.$(FILEEXT)
	cp ./libXEngine_ModulePlugin.$(FILEEXT) ../../XEngine_Release/libXEngine_ModulePlugin.$(FILEEXT)


CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(FILEEXT)                        