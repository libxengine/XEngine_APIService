RELEASE = 0
UNICODE = 0
PLATFORM=linux
FLAGS= 

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
	make -C $(THIRDPART_MODULE_JSONCPP) PLATFORM=$(PLATFORM) $(FLAGS)

libXEngine_ModuleConfigure.so:
	make -C $(MODULE_CONFIGURE_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
libXEngine_ModuleDatabase.so:
	make -C $(MODULE_DATABASE_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
libXEngine_ModuleProtocol.so:
	make -C $(MODULE_PROTOCOL_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
libXEngine_ModuleHelp.so:
	make -C $(MODULE_HELP_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
libXEngine_ModulePlugin.so:
	make -C $(MODULE_PLUGIN_PATH) PLATFORM=$(PLATFORM) $(FLAGS)

libModulePlugin_Zodiac.so:
	make -C $(PLUGIN_MODULE_ZODIAC) PLATFORM=$(PLATFORM) $(FLAGS)
libModulePlugin_Password.so:
	make -C $(PLUGIN_MODULE_PASSWORD) PLATFORM=$(PLATFORM) $(FLAGS)
libModulePlugin_Timezone.so:
	make -C $(PLUGIN_MODULE_TIMEZONE) PLATFORM=$(PLATFORM) $(FLAGS)
libModulePlugin_BMIndex.so:
	make -C $(PLUGIN_MODULE_BMINDEX) PLATFORM=$(PLATFORM) $(FLAGS)
libModulePlugin_Meter.so:
	make -C $(PLUGIN_MODULE_METER) PLATFORM=$(PLATFORM) $(FLAGS)
libModulePlugin_Phone.so:
	make -C $(PLUGIN_MODULE_PHONE) PLATFORM=$(PLATFORM) $(FLAGS)
libModulePlugin_IPAddr.so:
	make -C $(PLUGIN_MODULE_IPADDR) PLATFORM=$(PLATFORM) $(FLAGS)

XEngine_HttpApp.exe:
	make -C $(APP_HTTP_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
