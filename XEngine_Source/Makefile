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
PLUGIN_MODULE_TIMEZONE = ./XEngine_PluginModule/ModulePlugin_Timezone
PLUGIN_MODULE_BMINDEX = ./XEngine_PluginModule/ModulePlugin_BMIndex
PLUGIN_MODULE_METER = ./XEngine_PluginModule/ModulePlugin_Meter
PLUGIN_MODULE_PHONE = ./XEngine_PluginModule/ModulePlugin_Phone
PLUGIN_MODULE_IPADDR = ./XEngine_PluginModule/ModulePlugin_IPAddr

APP_CENTER_PATH = ./XEngine_ServiceApp/XEngine_CenterApp
APP_HTTP_PATH = ./XEngine_ServiceApp/XEngine_HttpApp

XENGINE_MODULES = libjsoncpp.so            \
                  libXEngine_ModuleConfigure.so libXEngine_ModuleDatabase.so libXEngine_ModuleProtocol.so libXEngine_ModuleHelp.so libXEngine_ModulePlugin.so  \
				  libModulePlugin_Zodiac.so libModulePlugin_Password.so libModulePlugin_Timezone.so libModulePlugin_BMIndex.so  libModulePlugin_Meter.so libModulePlugin_Phone.so libModulePlugin_IPAddr.so \
		   		  XEngine_HttpApp.exe

.PHONY:MakeAll 
MakeAll:$(XENGINE_MODULES)

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
libModulePlugin_Timezone.so:
	make -C $(PLUGIN_MODULE_TIMEZONE) $(FLAGS)
libModulePlugin_BMIndex.so:
	make -C $(PLUGIN_MODULE_BMINDEX) $(FLAGS)
libModulePlugin_Meter.so:
	make -C $(PLUGIN_MODULE_METER) $(FLAGS)
libModulePlugin_Phone.so:
	make -C $(PLUGIN_MODULE_PHONE) $(FLAGS)
libModulePlugin_IPAddr.so:
	make -C $(PLUGIN_MODULE_IPADDR) $(FLAGS)

XEngine_HttpApp.exe:
	make -C $(APP_HTTP_PATH) $(FLAGS)

SetFlags_Install:
	export FLAGS=InstallAll
InstallAll:SetFlags_Install $(NETENGINE_LIB) 
 
SetFlags_Clean:
	export FLAGS=CleanAll
CleanAll:SetFlags_Clean $(NETENGINE_LIB) 
