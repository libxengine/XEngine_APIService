CC = g++ -Wall
RELEASE = 0
UNICODE = 0  
LOADBIN = -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_Core -L /usr/local/lib/XEngine_Release/XEngine_HelpComponents -L /usr/local/lib/XEngine_Release/XEngine_RfcComponents -L /usr/local/lib/XEngine_Release/XEngine_NetHelp  \
          -L ../../XEngine_ModuleConfigure -L ../../XEngine_ModuleDatabase -L ../../XEngine_ModuleProtocol -L ../../XEngine_ModuleHelp \
		  -L ../../XEngine_ThirdPart/jsoncpp -L ../../XEngine_ThirdPart/opencc/ubuntu
LIB = -lXEngine_BaseLib -lXEngine_Algorithm -lXEngine_Core -lXEngine_ManagePool -lXEngine_OPenSsl -lHelpComponents_XLog -lRfcComponents_HttpServer -lNetHelp_APIHelp \
	  -lXEngine_ModuleConfigure -lXEngine_ModuleDatabase -lXEngine_ModuleProtocol -lXEngine_ModuleHelp                           \
	  -ljsoncpp -lopencc 
LIBEX = -static-libgcc -ldl -lrt -lpthread
LOADSO = -Wl,-rpath=./,--disable-new-dtags
LIBINCLUDE = XEngine_Configure.o XEngine_Network.o XEngine_HTTPTask.o XEngine_HttpApp.o        \
             HTTPTask_IPInfo.o HTTPTask_IDCard.o HTTPTask_Phone.o HTTPTask_Bank.o HTTPTask_Language.o HTTPTask_Translation.o

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
HTTPTask_IDCard.o:./XEngine_HTTPTask/HTTPTask_IDCard.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_IDCard.cpp
HTTPTask_Phone.o:./XEngine_HTTPTask/HTTPTask_Phone.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_Phone.cpp
HTTPTask_Bank.o:./XEngine_HTTPTask/HTTPTask_Bank.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_Bank.cpp
HTTPTask_Language.o:./XEngine_HTTPTask/HTTPTask_Language.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_Language.cpp
HTTPTask_Translation.o:./XEngine_HTTPTask/HTTPTask_Translation.cpp
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) ./XEngine_HTTPTask/HTTPTask_Translation.cpp

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
	       
