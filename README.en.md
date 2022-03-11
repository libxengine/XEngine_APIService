[中文](README.md) ||  [English](README.en.md)  
# XEngine_APIService
This repository has a development and master branch. If you want to use it, please use the master branch  

## Introduction
c c++ 接口服务器  
c c++ interface api service  
This is an api interface for information query service,At present, the information search service on the market need to charge, and our information search service is free and open source.  
This service mainly uses HTTP/V1.1 to implement various interface services  
This is a general information query service that does not contain any language attributes
The purpose of development and implementation based on libXEngine is a cross-platform network storage service  

## Software feature
1. support json and string stream methods to return the content of the query
2. support ip address location information query(IPV4 and IPV6)
3. support ID verification and information query
4. support phone number information query
5. Weather forecast (planned)
6. Lunar calendar conversion (planning)
7. News headlines (planned)
8. Standard height and weight (planned)
9. Zodiac Constellation (planned)
10. Password generator (planned)
11. World Time Zones (planned)
12. Oil price inquiry (planned)
13. Administrative zip code (planned)
14. Bank card verification (planned)
15. Exchange rate calculation (planned)
16. QR code generation (planned)
17. Simplified and Traditional Conversion (planned)
18. Oil price inquiry (planned)
19. Twenty-four solar terms (planned)
20. Xinhua Dictionary (planned)

## install

#### Requirements  
support system above windows 7sp1 and linux(ubuntu20.04,centos8)  
XEngine need V7.30 or above  

#### Windows
use vs open and complie  
You need to configure the environment in the following way, otherwise you may need to set the library directory in the project yourself  

##### XEngine
download xengine through git.read xengine project readme file to configure your env  

#### Linux
Linux use Makefile to complie  
supproted ubuntu x64 or centos x64  

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

## now task


## other problems   
You can refer to the document under the docment directory. It contains API protocol and service description.  

## Test Service
Address:app.xyry.org,Port:5501  
#### example
phone information query  
api:http://app.xyry.org:5501/api?function=phonequery&params1=13699439999&params2=0  
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
api;http://app.xyry.org:5501/api?function=ipquery&params1=1.29.164.255&params2=0  
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
api;http://app.xyry.org:5501/api?function=idquery&params1=511025198800000000&params2=0  
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