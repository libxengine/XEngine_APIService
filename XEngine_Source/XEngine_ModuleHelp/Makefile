CC = g++ -Wall -std=c++17 -fPIC
PLATFORM = linux
PLATVER = 
PLATDIR = 
FILEEXT = 
LIBFLAG = 
RELEASE = 0
UNICODE = 0
LOADHDR = -I ./ -I /usr/include/opencv4 -I /usr/local/include/opencv4 -I /usr/local/include/lua
LOADSO = 
LIB = -lXEngine_BaseLib -lXClient_Socket -lNetHelp_APIAddr
LIBEX = 
OBJECTS = ModuleHelp_IDCard.o ModuleHelp_Language.o ModuleHelp_P2PClient.o ModuleHelp_Locker.o ModuleHelp_QRCode.o ModuleHelp_SocketTest.o ModuleHelp_ImageGet.o ModuleHelp_ImageSet.o pch.o

MACRO_QR_SUPPORT := $(shell gcc -E -dM ../XEngine_BuildSwitch.h | grep _XENGINE_BUILD_SWITCH_QRDECODEC | cut -d ' ' -f 3)
MACRO_OPENCV_SUPPORT := $(shell gcc -E -dM ../XEngine_BuildSwitch.h | grep _XENGINE_BUILD_SWITCH_OPENCV | cut -d ' ' -f 3)

ifeq ($(MACRO_QR_SUPPORT),1)
	LIB += -lqrencode
endif
ifeq ($(MACRO_OPENCV_SUPPORT),1)
	LIB += -llzma -lpng16 -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -ltiff -lopencv_wechat_qrcode -ltesseract -lleptonica
endif

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
	LOADHDR += -I /opt/homebrew/opt/opencv/include/opencv4 -I /opt/homebrew/opt/tesseract/include -I /opt/homebrew/opt/qrencode/include -I /opt/homebrew/opt/lua/include
	LOADSO += -L /opt/homebrew/opt/opencv/lib -L /opt/homebrew/opt/tesseract/lib -L /opt/homebrew/opt/qrencode/lib -L /opt/homebrew/opt/lua/lib
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
ModuleHelp_ImageGet.o:./ModuleHelp_Image/ModuleHelp_ImageGet.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleHelp_Image/ModuleHelp_ImageGet.cpp
ModuleHelp_ImageSet.o:./ModuleHelp_Image/ModuleHelp_ImageSet.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleHelp_Image/ModuleHelp_ImageSet.cpp

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
