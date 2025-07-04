CC = g++ -Wall -std=c++20 -fPIC
PLATVER = 
FILEEXT = 
LIBFLAG = 
LOADHDR = -I ./ -I ../../XEngine_DependLibrary/XEngine_OPenSource/XEngine_Module/jsoncpp
LOADSO = -L ../../XEngine_DependLibrary/XEngine_OPenSource/XEngine_Module/jsoncpp
LIB = -lXEngine_BaseLib -lXEngine_Algorithm -ljsoncpp
LIBEX = 
OBJECTS = Plugin_Zodiac.o pch.o

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
	$(CC) $(DEBUG) $(OBJECTS) -o libModulePlugin_Zodiac.$(FILEEXT) $(LIBFLAG) $(LIB) $(LIBEX) $(LOADSO) $(LOADBIN)

Plugin_Zodiac.o:./Plugin_Zodiac/Plugin_Zodiac.cpp             
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./Plugin_Zodiac/Plugin_Zodiac.cpp 

pch.o:./pch.cpp                 		       	    
	$(CC) $(DEBUG) $(FLAGS) $(UNICODE) $(PLATVER) $(LOADHDR) ./pch.cpp


InstallAll:InstallSo 
InstallSo:./libModulePlugin_Zodiac.$(FILEEXT)
	cp ./libModulePlugin_Zodiac.$(FILEEXT) ../../../XEngine_Release/XEngine_LibPlugin/libModulePlugin_Zodiac.$(FILEEXT)

CleanAll:CleanObj CleanMk
CleanObj:                                               
	rm *.o
CleanMk:                             
	rm *.$(FILEEXT)                        