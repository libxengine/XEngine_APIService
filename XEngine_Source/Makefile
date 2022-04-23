RELEASE = 0
UNICODE = 0
#编译的选项参数
FLAGS = RELEASE=$(RELEASE)

#要编译的模块
THIRDPART_MODULE_JSONCPP = ./XEngine_ThirdPart/jsoncpp

MODULE_CONFIGURE_PATH = ./XEngine_ModuleConfigure
MODULE_DATABASE_PATH = ./XEngine_ModuleDatabase
MODULE_PROTOCOL_PATH = ./XEngine_ModuleProtocol
MODULE_HELP_PATH = ./XEngine_ModuleHelp
MODULE_PLUGIN_PATH = ./XEngine_ModulePlugin

PLUGIN_MODULE_ZODIAC = ./XEngine_PluginModule/ModulePlugin_Zodiac
PLUGIN_MODULE_PASSWORD = ./XEngine_PluginModule/ModulePlugin_Password

APP_CENTER_PATH = ./XEngine_ServiceApp/XEngine_CenterApp
APP_HTTP_PATH = ./XEngine_ServiceApp/XEngine_HttpApp

XENGINE_MODULES = libjsoncpp.so libopencc.so                                  \
                  libXEngine_ModuleConfigure.so libXEngine_ModuleDatabase.so libXEngine_ModuleProtocol.so libXEngine_ModuleHelp.so libXEngine_ModulePlugin.so  \
				  libModulePlugin_Zodiac.so libModulePlugin_Password.so \
		   XEngine_HttpApp.exe

.PHONY:MakeAll 
MakeAll:$(XENGINE_MODULES)

libopencc.so:
	cp -rf ./XEngine_ThirdPart/opencc/ubuntu/libopencc.so ../XEngine_Release/libopencc.so
libjsoncpp.so:
	make -C $(THIRDPART_MODULE_JSONCPP) $(FLAGS)

libXEngine_ModuleConfigure.so:
	make -C $(MODULE_CONFIGURE_PATH) $(FLAGS)
libXEngine_ModuleDatabase.so:
	make -C $(MODULE_DATABASE_PATH) $(FLAGS)
libXEngine_ModuleProtocol.so:
	make -C $(MODULE_PROTOCOL_PATH) $(FLAGS)
libXEngine_ModuleHelp.so:
	make -C $(MODULE_HELP_PATH) $(FLAGS)
libXEngine_ModulePlugin.so:
	make -C $(MODULE_PLUGIN_PATH) $(FLAGS)

libModulePlugin_Zodiac.so:
	make -C $(PLUGIN_MODULE_ZODIAC) $(FLAGS)
libModulePlugin_Password.so:
	make -C $(PLUGIN_MODULE_PASSWORD) $(FLAGS)

XEngine_HttpApp.exe:
	make -C $(APP_HTTP_PATH) $(FLAGS)

SetFlags_Install:
	export FLAGS=InstallAll
InstallAll:SetFlags_Install $(NETENGINE_LIB) 
 
SetFlags_Clean:
	export FLAGS=CleanAll
CleanAll:SetFlags_Clean $(NETENGINE_LIB) 
