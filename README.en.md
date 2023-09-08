[中文](README.md) ||  [English](README.en.md)  
# XEngine_APIService
This repository has a development and master branch. If you want to use it, please use the master branch  
As long as the repository is not in suspended state, we will maintain and develop it all the time, please use it with confidence  

## Introduction
c c++ 接口服务器  
c c++ interface api service  
This is an api interface for information query service,At present, the information search service on the market need to charge, and our information search service is free and open source.  
Not only is it a query service, but it can also provide functions such as machine management and process deamon.  
This service mainly uses HTTP/V1.1 to implement various interface services  
This is a general information query service that does not contain any language attributes
You can use this code to implement your own information query service, which supports querying any information  
The purpose of development and implementation based on libXEngine is a cross-platform network storage service  
and support plugin system,dll(so,dylib)module or lua script  

#### Why choose us

Support privatization deployment, free, safe, open source, controllable

## Software feature
1. permission verication
2. support ip address location information query
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
16. QR code generation and parse
17. Simplified and Traditional Conversion
18. Twenty-four solar terms (planned)
19. Xinhua Dictionary
20. Metering Conversion
21. network test
22. Distributed lock
23. short url creator and forward
24. local system time
25. math Calculation
26. log service
27. Plugin hot reload
28. Sensitive word detection
29. remote control(back management)
30. Image Process
31. process deamon

## install

#### XEngine Evn
you must install XEngine,need V8.x or above,install XEngine can be refer to xengine Readme docment  
GITEE:https://gitee.com/xyry/libxengine  
GITHUB:https://github.com/libxengine/xengine

##### fast to deployment 
git clone https://gitee.com/xyry/libxengine.git or git clone https://github.com/libxengine/xengine.git  
window Exection XEngine_WINEnv.bat   
Linux Exection:sudo ./XEngine_LINEnv.sh -i 3  
Macos Exection:./XEngine_LINEnv.sh -i 3

#### Database Env
MYSQL database version 8.0 or above is required. Create a table through CreateDatabase.sql, and then import other sql table
Modify the database configuration in XSQL in the configuration file to your  

#### Windows
need to vcpkg configure third-part env.refer vcpkg install guide.after installed and execution:vcpkg.exe install lua:x84-windows lua:x64-windows opencc:x84-windows opencc:x64-windows opencv[contrib]:x84-windows libqrencode:x84-windows opencv[contrib]:x64-windows libqrencode:x64-windows  
use vs open and compile,suport windows 7sp1 and above  
Just Run it

#### Linux
ubuntu:sudo apt install libopencc-dev  
centos:compile by self  
use makefile compile,UBUNTU22.04 x64 or RockyLinux 9 x64
Run it on the terminal

#### Macos
install opencc:brew install opencc  
use makefile compile,mac 13 and above  
Run it on the terminal

##### complie
execute command in XEngine_Source path  
make complie  
make FLAGS=InstallAll install  
make FLAGS=CleanAll clear 

## system task list
delete file  
delete dir  
upload a file to ftp  
Request a list of files in the folder  
execute program  
terminal process  
remote shutdown computre  
execute command  
information report  

#### use

1.  Switch to the MASTER branch
2.  download code
3.  complie
4.  install
5.  run

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
ZIPCode  
Api:http://app.xyry.org:5501/api?function=zipcode&params1=0  
```json
{
    "nZipCode":100010
}
```
Log  
Api:http://app.xyry.org:5501/api?function=log&params1=1  
```json
{
    "tszTableName":"xengine",
    "tszLogBuffer":"d12d",
    "nLogSize":4,
    "tszFileName":"file.cpp",
    "tszFuncName":"xengine_file_insert",
    "tszLogTimer":"2023-01-13 22:10:01",
    "nLogLine":102,
    "nLogLevel":4
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