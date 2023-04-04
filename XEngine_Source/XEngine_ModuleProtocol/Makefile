CC = g++ -Wall -std=c++17 -fPIC
PLATFORM = linux
PLATVER = 
PLATDIR = 
FILEEXT = 
LIBFLAG = 
RELEASE = 0
UNICODE = 0
LOADHDR = -I ./ -I ../XEngine_ThirdPart/jsoncpp
LOADSO = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L ../XEngine_ThirdPart/jsoncpp
LIB = -lXEngine_BaseLib -ljsoncpp
LIBEX = 
OBJECTS = ModuleProtocol_Packet.o ModuleProtocol_Parse.o pch.o

ifeq ($(RELEASE),1)
FLAGS = -c 
DEBUG = 
else
ifeq ($(PLATFORM),android)
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
else ifeq ($(PLATFORM),android)
	NDK_ROOT = $(HOME)/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++
	CC = $(NDK_ROOT) -target aarch64-linux-android30 -Wall -std=c++17 -fPIC
	PLATVER = -D __ANDROID__
	PLATDIR = XEngine_Android
	FILEEXT = so
	LIBFLAG = -shared
	LIBEX = -ldl
	LOADBIN = -Wl,-rpath=./,--disable-new-dtags
else ifeq ($(PLATFORM),mac)
	CC += -Wno-deprecated-declarations
	PLATVER = -D __MACOS__
	PLATDIR = XEngine_Mac
	FILEEXT = dylib
	LIBFLAG = -dynamiclib
	LIBEX = -lpthread -ldl
	LOADBIN = -Wl,-rpath,@loader_path/./
else ifeq ($(PLATFORM),ios)
	SDKPATH = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk
	CC += -arch arm64 -Wno-deprecated-declarations -isysroot ${SDKPATH} -miphoneos-version-min=13.0
	PLATVER = -D __IOS__
	PLATDIR = XEngine_IOS
	FILEEXT = dylib
	LIBFLAG = -dynamiclib
	LIBEX = -lpthread -ldl
	LOADBIN = -Wl,-rpath,@loader_path/./
endif


all:$(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) -o libXEngine_ModuleProtocol.$(FILEEXT) $(LIBFLAG) $(LIB) $(LIBEX) $(LOADSO) $(LOADBIN)

ModuleProtocol_Packet.o:./ModuleProtocol_Packet/ModuleProtocol_Packet.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleProtocol_Packet/ModuleProtocol_Packet.cpp 
ModuleProtocol_Parse.o:./ModuleProtocol_Parse/ModuleProtocol_Parse.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleProtocol_Parse/ModuleProtocol_Parse.cpp 
	
pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./pch.cpp


InstallAll:InstallSo 
InstallSo:./libXEngine_ModuleProtocol.$(FILEEXT)
	cp ./libXEngine_ModuleProtocol.$(FILEEXT) ../../XEngine_Release/libXEngine_ModuleProtocol.$(FILEEXT)


CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(FILEEXT)                        