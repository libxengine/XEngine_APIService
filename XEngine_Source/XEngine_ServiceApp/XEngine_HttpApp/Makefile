CC = g++ -Wall -std=c++20 -fPIC
PLATVER = 
FILEEXT = 
LIBFLAG = 
LOADHDR = -I ./ 
LOADSO = -L ../../XEngine_ModuleConfigure -L ../../XEngine_ModuleDatabase -L ../../XEngine_ModuleProtocol -L ../../XEngine_ModuleSystem -L ../../XEngine_ModuleHelp -L ../../XEngine_ModulePlugin   \
		 -L ../../XEngine_DependLibrary/XEngine_OPenSource/XEngine_Module/jsoncpp -L ../../XEngine_DependLibrary/XEngine_OPenSource/XEngine_Module/XEngine_InfoReport -L ../../XEngine_DependLibrary/XEngine_OPenSource/XEngine_Module/XEngine_Verification  \
		 -L ../../XEngine_DependLibrary/XEngine_IPMacData/XEngine_Source/XEngine_APIModuleIPMac -L ../../XEngine_DependLibrary/XEngine_PhoneData/XEngine_Source/XEngine_APIModulePhone
LIB = -lXEngine_BaseSafe -lXEngine_BaseLib -lXEngine_Algorithm -lXEngine_Core -lXEngine_ManagePool -lXEngine_Cryption -lXClient_Stream -lXClient_APIHelp -lXClient_Socket -lNetHelp_APIAddr -lNetHelp_XSocket -lHelpComponents_XLog -lRfcComponents_HttpProtocol -lRfcComponents_NatProtocol -lRfcComponents_NTPProtocol -lRfcComponents_DNSProtocol -lXEngine_ProcFile -lXEngine_SystemApi -lXEngine_AVHelp -lXEngine_VideoCodec -lXEngine_AudioCodec -lXEngine_AVCollect \
	  -lXEngine_ModuleConfigure -lXEngine_ModuleDatabase -lXEngine_ModuleProtocol -lXEngine_ModuleSystem -lXEngine_ModuleHelp -lXEngine_ModulePlugin                          \
	  -ljsoncpp -lXEngine_InfoReport -lXEngine_Verification  \
	  -lXEngine_APIModuleIPMac -lXEngine_APIModulePhone
LIBEX = 
OBJECTS = XEngine_Configure.o XEngine_Network.o XEngine_HTTPTask.o XEngine_PluginTask.o XEngine_HttpApp.o        \
		  RFCTask_Ntp.o RFCTask_Stun.o RFCTask_Dns.o \
          TaskGet_Bank.o TaskGet_IDCard.o TaskGet_Locker.o TaskGet_Translation.o TaskGet_Reload.o TaskGet_Weather.o TaskGet_IDRegion.o TaskGet_Oil.o TaskGet_APIModule.o \
		  TaskPost_DTest.o TaskPost_Log.o TaskPost_P2PClient.o TaskPost_PostCode.o TaskPost_QRCode.o TaskPost_ShortLink.o TaskPost_SocketTest.o TaskPost_WordFilter.o TaskPost_Image.o TaskPost_BackService.o TaskPost_Deamon.o TaskPost_Machine.o

ifeq ($(RELEASE),1)
FLAGS = -c -D _RELEASE
DEBUG = -O2
else
	ifeq ($(PLATFORM),mac)
		FLAGS = -c
		DEBUG = -g -D _DEBUG
	else
		FLAGS = -c -lc_p
		DEBUG = -g -pg -D _DEBUG
	endif
endif

ifeq ($(UNICODE),1)
override UNICODE := -D __UNICODE__
else
override UNICODE := -D __ANSI__
endif

ifeq ($(PLATFORM),linux)
	ifeq (/etc/redhat-release,$(wildcard /etc/redhat-release))
		PLATVER = -D __CENTOS__
	else
		PLATVER = -D __UBUNTU__
	endif
	CC += -Wformat-overflow=0
	FILEEXT = so
	LIBFLAG = -shared
	LIBEX = -lpthread -lrt -ldl
	LOADBIN = -Wl,-rpath=./:/usr/local/ffmpeg-xengine/lib,--disable-new-dtags
else ifeq ($(PLATFORM),mac)
	CC += -Wno-deprecated-declarations
	PLATVER = -D __MACOS__
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

RFCTask_Ntp.o:./XEngine_TaskRfc/RFCTask_Ntp.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskRfc/RFCTask_Ntp.cpp
RFCTask_Stun.o:./XEngine_TaskRfc/RFCTask_Stun.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskRfc/RFCTask_Stun.cpp
RFCTask_Dns.o:./XEngine_TaskRfc/RFCTask_Dns.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskRfc/RFCTask_Dns.cpp

TaskGet_Bank.o:./XEngine_TaskGet/TaskGet_Bank.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Bank.cpp
TaskGet_IDCard.o:./XEngine_TaskGet/TaskGet_IDCard.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_IDCard.cpp
TaskGet_Locker.o:./XEngine_TaskGet/TaskGet_Locker.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Locker.cpp
TaskGet_Translation.o:./XEngine_TaskGet/TaskGet_Translation.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Translation.cpp
TaskGet_Reload.o:./XEngine_TaskGet/TaskGet_Reload.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Reload.cpp
TaskGet_Weather.o:./XEngine_TaskGet/TaskGet_Weather.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Weather.cpp
TaskGet_IDRegion.o:./XEngine_TaskGet/TaskGet_IDRegion.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_IDRegion.cpp
TaskGet_Oil.o:./XEngine_TaskGet/TaskGet_Oil.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_Oil.cpp
TaskGet_APIModule.o:./XEngine_TaskGet/TaskGet_APIModule.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskGet/TaskGet_APIModule.cpp

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
TaskPost_Image.o:./XEngine_TaskPost/TaskPost_Image.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_Image.cpp
TaskPost_BackService.o:./XEngine_TaskPost/TaskPost_BackService.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_BackService.cpp
TaskPost_Deamon.o:./XEngine_TaskPost/TaskPost_Deamon.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_Deamon.cpp
TaskPost_Machine.o:./XEngine_TaskPost/TaskPost_Machine.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./XEngine_TaskPost/TaskPost_Machine.cpp

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
	       
