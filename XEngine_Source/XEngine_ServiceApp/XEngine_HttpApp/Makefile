CC = g++ -Wall -std=c++17 -fPIC -Wformat-overflow=0
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
LIB = -lXEngine_BaseLib -lXEngine_Algorithm -lXEngine_Core -lXEngine_ManagePool -lXEngine_OPenSsl -lHelpComponents_XLog -lRfcComponents_HttpProtocol -lNetHelp_APIClient \
	  -lXEngine_ModuleConfigure -lXEngine_ModuleDatabase -lXEngine_ModuleProtocol -lXEngine_ModuleHelp -lXEngine_ModulePlugin                          \
	  -ljsoncpp
LIBEX = 
OBJECTS = XEngine_Configure.o XEngine_Network.o XEngine_HTTPTask.o XEngine_PluginTask.o XEngine_HttpApp.o        \
          TaskGet_Bank.o TaskGet_IDCard.o TaskGet_Language.o TaskGet_Locker.o TaskGet_Translation.o TaskGet_Reload.o  \
		  TaskPost_DTest.o TaskPost_Log.o TaskPost_P2PClient.o TaskPost_PostCode.o TaskPost_QRCode.o TaskPost_ShortLink.o TaskPost_SocketTest.o TaskPost_WordFilter.o

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
	$(CC) $(DEBUG) $(OBJECTS) -o XEngine_APIServiceApp $(LIB) $(LIBEX) $(LOADSO) $(LOADBIN)
  
XEngine_Configure.o:./XEngine_Configure.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_Configure.cpp
XEngine_Network.o:./XEngine_Network.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_Network.cpp 
XEngine_HTTPTask.o:./XEngine_HTTPTask.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_HTTPTask.cpp
XEngine_PluginTask.o:./XEngine_PluginTask.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_PluginTask.cpp

TaskGet_Bank.o:./XEngine_TaskGet/TaskGet_Bank.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Bank.cpp
TaskGet_IDCard.o:./XEngine_TaskGet/TaskGet_IDCard.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_IDCard.cpp
TaskGet_Language.o:./XEngine_TaskGet/TaskGet_Language.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Language.cpp
TaskGet_Locker.o:./XEngine_TaskGet/TaskGet_Locker.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Locker.cpp
TaskGet_Translation.o:./XEngine_TaskGet/TaskGet_Translation.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Translation.cpp
TaskGet_Reload.o:./XEngine_TaskGet/TaskGet_Reload.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Reload.cpp

TaskPost_DTest.o:./XEngine_TaskPost/TaskPost_DTest.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_DTest.cpp
TaskPost_Log.o:./XEngine_TaskPost/TaskPost_Log.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_Log.cpp
TaskPost_P2PClient.o:./XEngine_TaskPost/TaskPost_P2PClient.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_P2PClient.cpp
TaskPost_PostCode.o:./XEngine_TaskPost/TaskPost_PostCode.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_PostCode.cpp
TaskPost_QRCode.o:./XEngine_TaskPost/TaskPost_QRCode.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_QRCode.cpp
TaskPost_ShortLink.o:./XEngine_TaskPost/TaskPost_ShortLink.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_ShortLink.cpp
TaskPost_SocketTest.o:./XEngine_TaskPost/TaskPost_SocketTest.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_SocketTest.cpp
TaskPost_WordFilter.o:./XEngine_TaskPost/TaskPost_WordFilter.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_WordFilter.cpp

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
	       
