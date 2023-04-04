CC = g++ -Wall -std=c++17 -fPIC
PLATFORM = linux
PLATVER = 
PLATDIR = 
FILEEXT = 
LIBFLAG = 
RELEASE = 0
UNICODE = 0
LOADHDR = -I ./ -I ../XEngine_ThirdPart/jsoncpp
LOADSO = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_Core -L /usr/local/lib/XEngine_Release/XEngine_HelpComponents -L /usr/local/lib/XEngine_Release/XEngine_RfcComponents -L /usr/local/lib/XEngine_Release/XEngine_NetHelp  \
		 -L ../../XEngine_ModuleConfigure -L ../../XEngine_ModuleDatabase -L ../../XEngine_ModuleProtocol -L ../../XEngine_ModuleHelp -L ../../XEngine_ModulePlugin   \
		 -L ../../XEngine_ThirdPart/jsoncpp
LIB = -lXEngine_BaseLib -lXEngine_Algorithm -lXEngine_Core -lXEngine_ManagePool -lXEngine_OPenSsl -lHelpComponents_XLog -lRfcComponents_HttpServer -lNetHelp_APIClient \
	  -lXEngine_ModuleConfigure -lXEngine_ModuleDatabase -lXEngine_ModuleProtocol -lXEngine_ModuleHelp -lXEngine_ModulePlugin                          \
	  -ljsoncpp
LIBEX = 
OBJECTS = XEngine_Configure.o XEngine_Network.o XEngine_HTTPTask.o XEngine_PluginTask.o XEngine_HttpApp.o        \
          HTTPTask_IDCard.o HTTPTask_Bank.o HTTPTask_Language.o HTTPTask_Translation.o HTTPTask_P2PClient.o HTTPTask_OPtions.o HTTPTask_Locker.o HTTPTask_PostCode.o HTTPTask_Log.o HTTPTask_QRCode.o HTTPTask_SocketTest.o

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
	$(CC) $(DEBUG) $(OBJECTS) -o XEngine_APIServiceApp $(LIB) $(LIBEX) $(LOADSO) $(LOADBIN)
  
XEngine_Configure.o:./XEngine_Configure.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_Configure.cpp
XEngine_Network.o:./XEngine_Network.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_Network.cpp 
XEngine_HTTPTask.o:./XEngine_HTTPTask.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask.cpp
XEngine_PluginTask.o:./XEngine_PluginTask.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_PluginTask.cpp

HTTPTask_IDCard.o:./XEngine_HTTPTask/HTTPTask_IDCard.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_IDCard.cpp
HTTPTask_Bank.o:./XEngine_HTTPTask/HTTPTask_Bank.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_Bank.cpp
HTTPTask_Language.o:./XEngine_HTTPTask/HTTPTask_Language.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_Language.cpp
HTTPTask_Translation.o:./XEngine_HTTPTask/HTTPTask_Translation.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_Translation.cpp
HTTPTask_P2PClient.o:./XEngine_HTTPTask/HTTPTask_P2PClient.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_P2PClient.cpp
HTTPTask_OPtions.o:./XEngine_HTTPTask/HTTPTask_OPtions.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_OPtions.cpp
HTTPTask_Locker.o:./XEngine_HTTPTask/HTTPTask_Locker.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_Locker.cpp
HTTPTask_PostCode.o:./XEngine_HTTPTask/HTTPTask_PostCode.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_PostCode.cpp
HTTPTask_Log.o:./XEngine_HTTPTask/HTTPTask_Log.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_Log.cpp
HTTPTask_QRCode.o:./XEngine_HTTPTask/HTTPTask_QRCode.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_QRCode.cpp
HTTPTask_SocketTest.o:./XEngine_HTTPTask/HTTPTask_SocketTest.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask/HTTPTask_SocketTest.cpp

XEngine_HttpApp.o:./XEngine_HttpApp.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HttpApp.cpp   


InstallAll:InstallApp
InstallApp:./XEngine_APIServiceApp
	cp -f ./XEngine_APIServiceApp ../../../XEngine_Release/XEngine_APIServiceApp

CleanAll:CleanObj CleanMk
CleanObj:                                              
	rm *.o
CleanMk:                                  
	rm XEngine_APIServiceApp     
	       
