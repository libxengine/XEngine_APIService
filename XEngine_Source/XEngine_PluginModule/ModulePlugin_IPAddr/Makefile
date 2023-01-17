CC = g++ -Wall -std=c++17 -fPIC -Wno-deprecated-declarations
SHAREFLAG = -shared
SHAREDLL = so
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./ -I ../../XEngine_ThirdPart/jsoncpp
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L ../../XEngine_ThirdPart/jsoncpp
LIB = -lXEngine_BaseLib -ljsoncpp
LIBEX = -ldl -lpthread
LOADSO = -Wl,-rpath=../,--disable-new-dtags
LIBINCLUDE = ModulePlugin_IPAddr.o ModulePlugin_Interface.o pch.o

ifeq ($(shell uname),Darwin)
	SHAREDLL = dylib
	SHAREFLAG = -dynamiclib
	LOADSO = 
else
	SHAREDLL = so
	SHAREFLAG = -shared
endif

ifeq ($(RELEASE),1)
FLAGS = -c -O2 
DEBUG = 
else
FLAGS = -c
DEBUG = -g
endif

ifeq ($(UNICODE),1)
UNICODE = -D _UNICODE
else
UNICODE = 
endif


all:$(LIBINCLUDE)
	$(CC) $(DEBUG) $(LIBINCLUDE) -o libModulePlugin_IPAddr.$(SHAREDLL) $(SHAREFLAG) -fPIC $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)

ModulePlugin_IPAddr.o:./ModulePlugin_IPAddr/ModulePlugin_IPAddr.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModulePlugin_IPAddr/ModulePlugin_IPAddr.cpp 
ModulePlugin_Interface.o:./ModulePlugin_Interface/ModulePlugin_Interface.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModulePlugin_Interface/ModulePlugin_Interface.cpp 

pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./pch.cpp


InstallAll:InstallSo 
InstallSo:./libModulePlugin_IPAddr.$(SHAREDLL)
	cp ./libModulePlugin_IPAddr.$(SHAREDLL) ../../../XEngine_Release/XEngine_LibPlugin/libModulePlugin_IPAddr.$(SHAREDLL)

CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(SHAREDLL)                        