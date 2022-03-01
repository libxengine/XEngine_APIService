[中文](README.md) ||  [English](README.en.md)  
# XEngine_APIService
This repository has a development and master branch. If you want to use it, please use the master branch  

## Introduction
c c++ 接口服务器  
c c++ interface api service  
This is an interface api service.  
This service mainly uses HTTP/V1.1 to implement various interface services  
The purpose of development and implementation based on libXEngine is a cross-platform network storage service  

## Software feature
1. support ip address location information query(IPV4 and IPV6)  

## install

#### Requirements  
support system above windows 7sp1 and linux(ubuntu20.04,centos8)  
XEngine need V7.24 or above  

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
5.  run

## directory struct
- XEngine_Docment   docment directory
- XEngine_Release   install directory
- XEngine_Source    code    directory  
- XEngine_APPClient client  code dir  

## now task


## other problems   
You can refer to the document under the docment directory. It contains API protocol and service description.  

## Test Service
Address:app.xyry.org or 159.75.200.173  
Port:HTTP Center Port 5501  

## Participate in contribution

1. Fork this code
2. Create new Feat_xxx branch
3. Submit the code
4. New Pull Request  

## Follow us
If you think this software is helpful to you, please give us a START

## post issues

if you have eny quest.post issues...
