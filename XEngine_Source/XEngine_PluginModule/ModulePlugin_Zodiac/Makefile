CC = g++ -Wall -std=c++17 -fPIC
SHAREFLAG = -shared
SHAREDLL = so
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./ -I ../../XEngine_ThirdPart/jsoncpp
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L ../../XEngine_ThirdPart/jsoncpp
LIB = -lXEngine_BaseLib -lXEngine_Algorithm -ljsoncpp
LIBEX = -ldl -lpthread
LOADSO = -Wl,-rpath=../,--disable-new-dtags
LIBINCLUDE = Plugin_Zodiac.o pch.o

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
	$(CC) $(DEBUG) $(LIBINCLUDE) -o libModulePlugin_Zodiac.$(SHAREDLL) $(SHAREFLAG) -fPIC $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)

Plugin_Zodiac.o:./Plugin_Zodiac/Plugin_Zodiac.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./Plugin_Zodiac/Plugin_Zodiac.cpp 

pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./pch.cpp


InstallAll:InstallSo 
InstallSo:./libModulePlugin_Zodiac.$(SHAREDLL)
	cp ./libModulePlugin_Zodiac.$(SHAREDLL) ../../../XEngine_Release/XEngine_Plugin/libModulePlugin_Zodiac.$(SHAREDLL)

CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(SHAREDLL)                        