CC = g++ -Wall
RELEASE = 0
UNICODE = 0  
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_Core -L /usr/local/lib/XEngine_Release/XEngine_HelpComponents -L /usr/local/lib/XEngine_Release/XEngine_RfcComponents -L /usr/local/lib/XEngine_Release/XEngine_NetHelp  \
          -L ../../XEngine_ModuleConfigure -L ../../XEngine_ModuleDatabase -L ../../XEngine_ModuleProtocol -L ../../XEngine_ModuleHelp -L ../../XEngine_ModulePlugin   \
		  -L ../../XEngine_ThirdPart/jsoncpp
LIB = -lXEngine_BaseLib -lXEngine_Algorithm -lXEngine_Core -lXEngine_ManagePool -lXEngine_OPenSsl -lHelpComponents_XLog -lRfcComponents_HttpServer -lNetHelp_APIClient \
	  -lXEngine_ModuleConfigure -lXEngine_ModuleDatabase -lXEngine_ModuleProtocol -lXEngine_ModuleHelp -lXEngine_ModulePlugin                          \
	  -ljsoncpp
LIBEX = -ldl -lpthread
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = XEngine_Configure.o XEngine_Network.o XEngine_HTTPTask.o XEngine_PluginTask.o XEngine_HttpApp.o        \
             HTTPTask_IDCard.o HTTPTask_Bank.o HTTPTask_Language.o HTTPTask_Translation.o HTTPTask_P2PClient.o HTTPTask_OPtions.o HTTPTask_Locker.o HTTPTask_PostCode.o HTTPTask_Log.o

ifeq ($(shell uname),Darwin)
	LOADSO = 
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
	$(CC) $(DEBUG) $(LIBINCLUDE) -o XEngine_APIServiceApp $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)
  
XEngine_Configure.o:./XEngine_Configure.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_Configure.cpp
XEngine_Network.o:./XEngine_Network.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_Network.cpp 
XEngine_HTTPTask.o:./XEngine_HTTPTask.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask.cpp
XEngine_PluginTask.o:./XEngine_PluginTask.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_PluginTask.cpp

HTTPTask_IDCard.o:./XEngine_HTTPTask/HTTPTask_IDCard.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_IDCard.cpp
HTTPTask_Bank.o:./XEngine_HTTPTask/HTTPTask_Bank.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_Bank.cpp
HTTPTask_Language.o:./XEngine_HTTPTask/HTTPTask_Language.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_Language.cpp
HTTPTask_Translation.o:./XEngine_HTTPTask/HTTPTask_Translation.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_Translation.cpp
HTTPTask_P2PClient.o:./XEngine_HTTPTask/HTTPTask_P2PClient.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_P2PClient.cpp
HTTPTask_OPtions.o:./XEngine_HTTPTask/HTTPTask_OPtions.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_OPtions.cpp
HTTPTask_Locker.o:./XEngine_HTTPTask/HTTPTask_Locker.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_Locker.cpp
HTTPTask_PostCode.o:./XEngine_HTTPTask/HTTPTask_PostCode.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_PostCode.cpp
HTTPTask_Log.o:./XEngine_HTTPTask/HTTPTask_Log.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_Log.cpp

XEngine_HttpApp.o:./XEngine_HttpApp.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HttpApp.cpp   


InstallAll:InstallApp
InstallApp:./XEngine_APIServiceApp
	cp -f ./XEngine_APIServiceApp ../../../XEngine_Release/XEngine_APIServiceApp

CleanAll:CleanObj CleanMk
CleanObj:                                              
	rm *.o
CleanMk:                                  
	rm XEngine_APIServiceApp     
	       
