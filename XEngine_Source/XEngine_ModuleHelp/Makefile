CC = g++ -Wall -std=c++17 -fPIC
PLATFORM = linux
PLATVER = 
PLATDIR = 
FILEEXT = 
LIBFLAG = 
RELEASE = 0
UNICODE = 0
LOADHDR = -I ./ -I /usr/include/opencv4
LOADSO = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_Client 
LIB = -lXEngine_BaseLib -lXClient_Socket -lopencc -llzma -lpng16 -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -ltiff
LIBEX = 
OBJECTS = ModuleHelp_IDCard.o ModuleHelp_Language.o ModuleHelp_P2PClient.o ModuleHelp_Locker.o ModuleHelp_QRCode.o ModuleHelp_SocketTest.o pch.o


ifeq ($(RELEASE),1)
FLAGS = -c 
DEBUG = 
else
FLAGS = -c -lc_p
DEBUG = -g -pg 
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
	else
		PLATVER = -D __UBUNTU__
		PLATDIR = XEngine_Linux/Ubuntu
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
	LIBEX = -lpthread -ldl
	LOADBIN = -Wl,-rpath,@loader_path/./
endif


all:$(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) -o libXEngine_ModuleHelp.$(FILEEXT) $(LIBFLAG) $(LIB) $(LIBEX) $(LOADSO) $(LOADBIN)

ModuleHelp_IDCard.o:./ModuleHelp_IDCard/ModuleHelp_IDCard.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleHelp_IDCard/ModuleHelp_IDCard.cpp 
ModuleHelp_Language.o:./ModuleHelp_Language/ModuleHelp_Language.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleHelp_Language/ModuleHelp_Language.cpp 
ModuleHelp_P2PClient.o:./ModuleHelp_P2PClient/ModuleHelp_P2PClient.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleHelp_P2PClient/ModuleHelp_P2PClient.cpp
ModuleHelp_Locker.o:./ModuleHelp_Locker/ModuleHelp_Locker.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleHelp_Locker/ModuleHelp_Locker.cpp
ModuleHelp_QRCode.o:./ModuleHelp_QRCode/ModuleHelp_QRCode.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleHelp_QRCode/ModuleHelp_QRCode.cpp
ModuleHelp_SocketTest.o:./ModuleHelp_SocketTest/ModuleHelp_SocketTest.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleHelp_SocketTest/ModuleHelp_SocketTest.cpp

pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./pch.cpp


InstallAll:InstallSo 
InstallSo:./libXEngine_ModuleHelp.$(FILEEXT)
	cp ./libXEngine_ModuleHelp.$(FILEEXT) ../../XEngine_Release/libXEngine_ModuleHelp.$(FILEEXT)


CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(FILEEXT)                        