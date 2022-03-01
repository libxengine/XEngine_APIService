CC = g++ -Wall
RELEASE = 0
UNICODE = 0  
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_Core -L /usr/local/lib/XEngine_Release/XEngine_HelpComponents -L /usr/local/lib/XEngine_Release/XEngine_RfcComponents -L ../../XEngine_ThirdPart/jsoncpp -L ../../XEngine_ModuleConfigure -L ../../XEngine_ModuleDatabase -L ../../XEngine_ModuleProtocol
LIB = -lXEngine_BaseLib -lXEngine_Algorithm -lXEngine_Core -lXEngine_ManagePool -lHelpComponents_XLog -lRfcComponents_HttpServer -ljsoncpp -lXEngine_ModuleConfigure -lXEngine_ModuleDatabase -lXEngine_ModuleProtocol
LIBEX = -static-libgcc -ldl -lrt -lpthread
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = XEngine_Configure.o XEngine_Network.o XEngine_HTTPTask.o HTTPTask_IPInfo.o XEngine_HttpApp.o

ifeq ($(RELEASE),1)
FLAGS = -c -O2 
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

all:$(LIBINCLUDE)
	$(CC) $(DEBUG) $(LIBINCLUDE) -o XEngine_HttpApp $(LOADBIN) $(LIB) $(LIBEX) $(LOADSO)
  
XEngine_Configure.o:./XEngine_Configure.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_Configure.cpp
XEngine_Network.o:./XEngine_Network.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_Network.cpp 
XEngine_HTTPTask.o:./XEngine_HTTPTask.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask.cpp

HTTPTask_IPInfo.o:./XEngine_HTTPTask/HTTPTask_IPInfo.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_IPInfo.cpp
	
XEngine_HttpApp.o:./XEngine_HttpApp.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HttpApp.cpp   


InstallAll:InstallApp
InstallApp:./XEngine_HttpApp
	cp -f ./XEngine_HttpApp ../../../XEngine_Release/XEngine_HttpApp

CleanAll:CleanObj CleanMk
CleanObj:                                              
	rm *.o
CleanMk:                                  
	rm XEngine_HttpApp     
	       
