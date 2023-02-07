CC = g++ -Wall -std=c++17 -fPIC -Wno-deprecated-declarations
SHAREFLAG = -shared
SHAREDLL = so
RELEASE = 0
UNICODE = 0
INCLUDE = -I ./ -I /usr/include/opencv4
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_Client 
LIB = -lXEngine_BaseLib -lXClient_Socket -lopencc
LIBEX = -ldl -lpthread
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = ModuleHelp_IDCard.o ModuleHelp_Language.o ModuleHelp_P2PClient.o ModuleHelp_Locker.o ModuleHelp_QRCode.o ModuleHelp_SocketTest.o pch.o

ifeq ($(OS),Windows_NT)
	PLATFORM="Windows"
else
	ifeq ($(shell uname),Darwin)
		PLATFORM="MacOS"
	else
		ifeq ($(FILECENTOS), $(wildcard $(FILECENTOS)))
#			LIB += -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
		else
#			LIB += -llzma -lpng16 -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -ltiff
		endif 
	endif
endif

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
ModuleHelp_QRCode.o:./ModuleHelp_QRCode/ModuleHelp_QRCode.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModuleHelp_QRCode/ModuleHelp_QRCode.cpp
ModuleHelp_SocketTest.o:./ModuleHelp_SocketTest/ModuleHelp_SocketTest.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(INCLUDE) ./ModuleHelp_SocketTest/ModuleHelp_SocketTest.cpp

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