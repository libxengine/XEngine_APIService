CC = g++ -Wall -std=c++17 -fPIC
PLATFORM = linux
PLATVER = 
PLATDIR = 
FILEEXT = 
LIBFLAG = 
RELEASE = 0
UNICODE = 0
LOADHDR = -I ./
LOADSO = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib
LIB = -lXEngine_BaseLib
LIBEX = 
OBJECTS = ModulePlugin_LibCore.o ModulePlugin_LuaCore.o ModulePlugin_Loader.o pch.o

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
	LIB += -llua5.3
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
	LIB += -llua
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