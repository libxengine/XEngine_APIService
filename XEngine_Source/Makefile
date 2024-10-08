RELEASE = 0
UNICODE = 0
PLATFORM=linux
FLAGS=

#要编译的模块
MODULE_CONFIGURE_PATH = ./XEngine_ModuleConfigure
MODULE_DATABASE_PATH = ./XEngine_ModuleDatabase
MODULE_PROTOCOL_PATH = ./XEngine_ModuleProtocol
MODULE_SYSTEM_PATH = ./XEngine_ModuleSystem
MODULE_HELP_PATH = ./XEngine_ModuleHelp
MODULE_PLUGIN_PATH = ./XEngine_ModulePlugin

PLUGIN_MODULE_ZODIAC = ./XEngine_PluginModule/ModulePlugin_Zodiac
PLUGIN_MODULE_PASSWORD = ./XEngine_PluginModule/ModulePlugin_Password
PLUGIN_MODULE_TIMEZONE = ./XEngine_PluginModule/ModulePlugin_Timezone
PLUGIN_MODULE_BMINDEX = ./XEngine_PluginModule/ModulePlugin_BMIndex
PLUGIN_MODULE_METER = ./XEngine_PluginModule/ModulePlugin_Meter

THIRDPART_MODULE_JSONCPP = ./XEngine_Depend/XEngine_Module/jsoncpp
THIRDPART_MODULE_REPORT = ./XEngine_Depend/XEngine_Module/XEngine_InfoReport

APIMODULE_PHONE_PATH = ./XEngine_DBDepend/XEngine_PhoneData/Source/C/XEngine_APIModulePhone
APIMODULE_IPMAC_PATH = ./XEngine_DBDepend/XEngine_IPMacData/XEngine_Source/XEngine_APIModuleIPMac

APP_HTTP_PATH = ./XEngine_ServiceApp/XEngine_HttpApp

ifeq ($(PLATFORM),linux)
	FILEEXT = so
else ifeq ($(PLATFORM),mac)
	FILEEXT = dylib
endif

XENGINE_MODULES = libjsoncpp.so libXEngine_InfoReport.so          \
				  libXEngine_ModuleConfigure.so libXEngine_ModuleDatabase.so libXEngine_ModuleProtocol.so libXEngine_ModuleSystem.so libXEngine_ModuleHelp.so libXEngine_ModulePlugin.so  \
				  libModulePlugin_Zodiac.so libModulePlugin_Password.so libModulePlugin_Timezone.so libModulePlugin_BMIndex.so  libModulePlugin_Meter.so \
				  libXEngine_APIModulePhone.so libXEngine_APIModuleIPMac.so \
		   		  XEngine_HttpApp.exe

.PHONY:MakeAll 
MakeAll:$(XENGINE_MODULES)

libXEngine_ModuleConfigure.so:
	make -C $(MODULE_CONFIGURE_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
libXEngine_ModuleDatabase.so:
	make -C $(MODULE_DATABASE_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
libXEngine_ModuleProtocol.so:
	make -C $(MODULE_PROTOCOL_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
libXEngine_ModuleSystem.so:
	make -C $(MODULE_SYSTEM_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
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

libjsoncpp.so:
ifeq ($(FLAGS), InstallAll)
	cp $(THIRDPART_MODULE_JSONCPP)/libjsoncpp.$(FILEEXT) ../XEngine_Release/
else
	make -C $(THIRDPART_MODULE_JSONCPP) PLATFORM=$(PLATFORM) $(FLAGS)
endif
libXEngine_InfoReport.so:
ifeq ($(FLAGS), InstallAll)
	cp $(THIRDPART_MODULE_REPORT)/libXEngine_InfoReport.$(FILEEXT) ../XEngine_Release/
else
	make -C $(THIRDPART_MODULE_REPORT) PLATFORM=$(PLATFORM) $(FLAGS)
endif

libXEngine_APIModulePhone.so:
ifeq ($(FLAGS), InstallAll)
	cp $(APIMODULE_PHONE_PATH)/libXEngine_APIModulePhone.$(FILEEXT) ../XEngine_Release/
else
	make -C $(APIMODULE_PHONE_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
endif
libXEngine_APIModuleIPMac.so:
ifeq ($(FLAGS), InstallAll)
	cp $(APIMODULE_IPMAC_PATH)/libXEngine_APIModuleIPMac.$(FILEEXT) ../XEngine_Release/
else
	make -C $(APIMODULE_IPMAC_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
endif
	
XEngine_HttpApp.exe:
	make -C $(APP_HTTP_PATH) PLATFORM=$(PLATFORM) $(FLAGS)
