CC = g++ -Wall -std=c++20 -fPIC
PLATVER = 
FILEEXT = 
LIBFLAG = 
LOADHDR = -I ./ 
LOADSO = 
LIB = -lXEngine_BaseLib -lHelpComponents_DataBase
LIBEX = 
OBJECTS = ModuleDatabase_IDCard.o ModuleDatabase_Bank.o ModuleDatabase_ZIPCode.o ModuleDatabase_XLog.o ModuleDatabase_ShortLink.o ModuleDatabase_WordFilter.o ModuleDatabase_Machine.o ModuleDatabase_OilInfo.o pch.o

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
	FILEEXT = so
	LIBFLAG = -shared
	LIBEX = -lpthread -lrt -ldl
	LOADBIN = -Wl,-rpath=./,--disable-new-dtags
else ifeq ($(PLATFORM),mac)
	CC += -Wno-deprecated-declarations
	PLATVER = -D __MACOS__
	FILEEXT = dylib
	LIBFLAG = -dynamiclib
	LIBEX = -lpthread -ldl
	LOADBIN = -Wl,-rpath,@loader_path/./
endif


all:$(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) -o libXEngine_ModuleDatabase.$(FILEEXT) $(LIBFLAG) $(LIB) $(LIBEX) $(LOADSO) $(LOADBIN)

ModuleDatabase_IDCard.o:./ModuleDatabase_IDCard/ModuleDatabase_IDCard.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleDatabase_IDCard/ModuleDatabase_IDCard.cpp 
ModuleDatabase_Bank.o:./ModuleDatabase_Bank/ModuleDatabase_Bank.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleDatabase_Bank/ModuleDatabase_Bank.cpp
ModuleDatabase_ZIPCode.o:./ModuleDatabase_ZIPCode/ModuleDatabase_ZIPCode.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleDatabase_ZIPCode/ModuleDatabase_ZIPCode.cpp
ModuleDatabase_XLog.o:./ModuleDatabase_XLog/ModuleDatabase_XLog.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleDatabase_XLog/ModuleDatabase_XLog.cpp
ModuleDatabase_ShortLink.o:./ModuleDatabase_ShortLink/ModuleDatabase_ShortLink.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleDatabase_ShortLink/ModuleDatabase_ShortLink.cpp
ModuleDatabase_WordFilter.o:./ModuleDatabase_WordFilter/ModuleDatabase_WordFilter.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleDatabase_WordFilter/ModuleDatabase_WordFilter.cpp
ModuleDatabase_Machine.o:./ModuleDatabase_Machine/ModuleDatabase_Machine.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleDatabase_Machine/ModuleDatabase_Machine.cpp
ModuleDatabase_OilInfo.o:./ModuleDatabase_OilInfo/ModuleDatabase_OilInfo.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./ModuleDatabase_OilInfo/ModuleDatabase_OilInfo.cpp

pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./pch.cpp


InstallAll:InstallSo 
InstallSo:./libXEngine_ModuleDatabase.$(FILEEXT)
	cp ./libXEngine_ModuleDatabase.$(FILEEXT) ../../XEngine_Release/libXEngine_ModuleDatabase.$(FILEEXT)


CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(FILEEXT)                        