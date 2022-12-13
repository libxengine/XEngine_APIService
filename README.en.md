[中文](README.md) ||  [English](README.en.md)  
# XEngine_APIService
This repository has a development and master branch. If you want to use it, please use the master branch  
As long as the repository is not in suspended state, we will maintain and develop it all the time, please use it with confidence  

## Introduction
c c++ 接口服务器  
c c++ interface api service  
This is an api interface for information query service,At present, the information search service on the market need to charge, and our information search service is free and open source.  
This service mainly uses HTTP/V1.1 to implement various interface services  
This is a general information query service that does not contain any language attributes
You can use this code to implement your own information query service, which supports querying any information  
The purpose of development and implementation based on libXEngine is a cross-platform network storage service  
and support plugin system,dll(so,dylib)module or lua script  

#### Why choose us

Support privatization deployment, free, safe, open source, controllable

## Software feature
1. permission verication
2. support ip address location information query(IPV4 and IPV6)
3. support ID verification and information query
4. support phone number information query
5. Weather forecast (planned)
6. Lunar calendar conversion (planning)
7. News headlines (planned)
8. Standard height and weight
9. Zodiac Constellation
10. Password generator
11. World Time Zones
12. Oil price inquiry (planned)
13. Administrative zip code
14. Bank card verification
15. Exchange rate calculation (planned)
16. QR code generation and parse (planned)
17. Simplified and Traditional Conversion
18. Twenty-four solar terms (planned)
19. Xinhua Dictionary
20. Metering Conversion
21. CDKey Creator
22. Distributed lock
23. short url creator
24. local system time
25. math Calculation
26. log service(plan)

## install

#### XEngine Evn
you must install XEngine,need V7.38 or above,install XEngine can be refer to xengine Readme docment  
GITEE:https://gitee.com/xyry/libxengine  
GITHUB:https://github.com/libxengine/xengine

##### fast to deployment 
git clone https://gitee.com/xyry/libxengine.git or git clone https://github.com/libxengine/xengine.git  
window Exection XEngine_WINEnv.bat   
Linux Exection:sudo ./XEngine_LINEnv.sh -i 3  
Macos Exection:./XEngine_LINEnv.sh -i 3

#### Windows
need to vcpkg configure third-part env.refer vcpkg install guide.after installed and execution:vcpkg.exe install lua lua:x64-windows opencc opencc:x64-windows  
use vs open and compile,suport windows 7sp1 and above  
Just Run it

#### Linux
install opencc,ubuntu:sudo apt install libopencc-dev  
centos:compile by self  
use makefile compile,UBUNTU20.04 x64 or CENTOS8 x64  
Run it on the terminal

#### Macos
install opencc:brew install opencc  
use makefile compile,mac 12 and above  
Run it on the terminal

##### complie
execute command in XEngine_Source path  
make complie  
make FLAGS=InstallAll install  
make FLAGS=CleanAll clear  

#### use

1.  Switch to the MASTER branch
2.  download code
3.  complie
4.  install
5.  uncompress /XEngine_Release/XEngine_DBFile/ipdata.rar into current dir
6.  run

## directory struct
- XEngine_Docment   docment directory
- XEngine_Release   install directory
- XEngine_Source    code    directory  
- XEngine_APPClient client  code dir  

## Plugin description
You can refer to the project under XEngine_PluginModule to write the plugin  
The written plugin needs to be configured via JSON to be enabled  

## Test Server
Address:app.xyry.org,Port:5501  

## now task

## other problems   
You can refer to the document under the docment directory. It contains API protocol and service description.  

## Test Service
Address:app.xyry.org,Port:5501  
#### example
For more information please refer to the documentation  
phone information query  
api:http://app.xyry.org:5501/api?function=phone&params1=13699439999
```json
{
    "code":0,
    "data":{
        "nAreaCode":28,
        "nPhoneNumber":13699439999,
        "nZipCode":610000,
        "tszCity":"成都",
        "tszProvincer":"四川"
    },
    "msg":"success"
}
```
ip address information  
api:http://app.xyry.org:5501/api?function=ip&params1=1.29.164.255
```json
{
    "code":0,
    "data":{
        "tszIPAddr":"1.29.164.255",
        "tszIPAddress":"内蒙古通辽市霍林郭勒市",
        "tszIPCity":"通辽市",
        "tszIPCountry":"中国",
        "tszIPCounty":"霍林郭勒市",
        "tszIPEnd":"1.29.164.255",
        "tszIPISP":"联通",
        "tszIPProvince":"内蒙古",
        "tszIPStart":"1.29.164.0",
        "tszIPTime":"2021-11-03 07:33:50"
    },
    "msg":"success"
}
```
id information query  
api:http://app.xyry.org:5501/api?function=id&params1=511025198800000000
```json
{
    "code":0,
    "data":{
        "nBirthDay":00,
        "nBirthMonth":00,
        "nBirthYear":1988,
        "nCheck":2,
        "nPoliceID":87,
        "nSex":1,
        "tszCity":"内江市",
        "tszCounty":"资中县",
        "tszIDNumber":"511025198800000000",
        "tszProvincer":"四川省"
    },
    "msg":"success"
}
```
bank card ver  
api:http://app.xyry.org:5501/api?function=bank&params1=6214832830000000
```json
{
    "code":0,
    "data":{
        "enBankType":2,
        "tszBankAbridge":"CMB",
        "tszBankName":"招商银行",
        "tszBankNumber":"6214832830000000"
    },
    "msg":"success"
}
```
language  
api:http://app.xyry.org:5501/api?function=language&params1=简体到繁体&params2=1
```json
{
    "code":0,
    "data":{
        "enType":1,
        "tszDestStr":"簡體到繁體",
        "tszSourceStr":"简体到繁体"
    },
    "msg":"success"
}
```
translation  
api:http://app.xyry.org:5501/api?function=translation&params1=中国&params2=0
```json
{
    "code":0,
    "data":{
        "enType":0,
        "tszDestStr":"China",
        "tszSourceStr":"中国"
    },
    "msg":"success"
}
```
Authorize CDKey  
Api:http://app.xyry.org:5501/api?function=cdkey&params1=0
```json
{
    "tszAddr":"服务器地址",
    "nPort":5000,
    "st_AuthAppInfo":{
        "tszAppName":"自定义名称",
        "tszAppVer":"自定义版本"
    },
    "st_AuthRegInfo":{
        "tszHardware":"硬件吗",
        "enSerialType":1,
        "enRegType":1,
        "enHWType":1
    },
    "st_AuthUserInfo":{
        "tszUserName":"注册的用户名",
        "tszUserContact":"联系方式",
        "tszCustom":"自定义,可选参数"
    }
}
```
Distributed Lock  
Api:http://app.xyry.org:5501/api?function=lock&params1=1000154321&params2=1
```json
{
    "code":0,
    "data":{
        "xhToken":1000154321
    },
    "msg":"success"
}
```
## Participate in contribution
I hope you will submit more code to participate in the contribution  

1. Fork this code
2. Create new Feat_xxx branch
3. Submit the code
4. New Pull Request  

## Follow us
If you think this software is helpful to you, please give us a START

## post issues

if you have eny quest.post issues...