CC = g++ -Wall -std=c++17 -fPIC
SHAREFLAG = -shared
SHAREDLL = so
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib 
LIB = -lXEngine_BaseLib -lopencc
LIBEX = -ldl -lpthread
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = ModuleHelp_IDCard.o ModuleHelp_Language.o ModuleHelp_P2PClient.o ModuleHelp_Locker.o pch.o

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
	$(CC) $(DEBUG) $(LIBINCLUDE) -o libXEngine_ModuleHelp.$(SHAREDLL) $(SHAREFLAG) -fPIC $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)

ModuleHelp_IDCard.o:./ModuleHelp_IDCard/ModuleHelp_IDCard.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModuleHelp_IDCard/ModuleHelp_IDCard.cpp 
ModuleHelp_Language.o:./ModuleHelp_Language/ModuleHelp_Language.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModuleHelp_Language/ModuleHelp_Language.cpp 
ModuleHelp_P2PClient.o:./ModuleHelp_P2PClient/ModuleHelp_P2PClient.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModuleHelp_P2PClient/ModuleHelp_P2PClient.cpp
ModuleHelp_Locker.o:./ModuleHelp_Locker/ModuleHelp_Locker.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModuleHelp_Locker/ModuleHelp_Locker.cpp

pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./pch.cpp


InstallAll:InstallSo 
InstallSo:./libXEngine_ModuleHelp.$(SHAREDLL)
	cp ./libXEngine_ModuleHelp.$(SHAREDLL) ../../XEngine_Release/libXEngine_ModuleHelp.$(SHAREDLL)


CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(SHAREDLL)                        