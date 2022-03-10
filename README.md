[中文](README.md) ||  [English](README.en.md)  
# XEngine_APIService
本仓库有开发和主分支,如果要使用,请使用master分支下的代码  

## 介绍
c c++ 接口服务器  
c c++ interface api service  
这是一个信息查询的API接口服务,目前市面上的信息查询服务都需要收费,而我们这个信息查询服务属于免费开源的.  
这个服务主要使用HTTP/V1.1实现各种接口服务.  
这是一个不包含任何语言属性的通用信息查询服务.  
基于libXEngine开发并实现的一套简洁高性能跨平台接口服务  

## 软件特性
1. 支持JSON和字符串流方式返回查询的内容
2. 支持IP地址位置信息查询(IPV4和IPV6)
3. 支持身份证校验与信息查询
4. 支持手机号信息归属查询

## 安装教程

#### 版本需求
支持WINDOWS 7SP1和LINUX(UBUNT20.04,CENTOS8)以上系统  
XEngine版本需要V7.30或者以上版本  

#### Windows
使用VS打开并且编译
你需要按照下面的方式配置环境,不然你可能需要自己在项目中设置库目录

##### XEngine环境
XEngine通过GIT下载,参考XEngine项目的readme配置环境  

#### Linux
Linux使用Makefile编译  
UBUNTU20.04 x64或者CENTOS8 x64均可  

##### 编译命令
在XEngine_Source目录下执行命令  
make 编译  
make FLAGS=InstallAll 安装库程序  
make FLAGS=CleanAll 清理编译  

#### 使用说明

1.  切换到MASTER分支
2.  下载代码
3.  编译
4.  安装
5.  解压/XEngine_Release/XEngine_DBFile/ipdata.rar 到当前目录
6.  运行

## 目录结构
- XEngine_Docment    文档目录结构  
- XEngine_Release    安装目录结构  
- XEngine_Source     源代目录结构  
- XEngine_APPClient  客户端演示代码  

## 当前任务


## 其他问题  
你可以参考docment目录下的文档.里面包含了API协议和服务说明.

## 测试服务器
地址:app.xyry.org,端口:5501  
#### 测试接口示例
手机信息查询  
接口:http://app.xyry.org:5501/api?function=phonequery&params1=13699439999&params2=0  
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
IP地址查询  
接口;http://app.xyry.org:5501/api?function=ipquery&params1=1.29.164.255&params2=0  
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
身份证查询  
接口;http://app.xyry.org:5501/api?function=idquery&params1=511025198800000000&params2=0  
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
## 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request  

## 关注我们
如果你觉得这个软件对你有帮助,请你给我们一个START吧

## 提交问题

如果你有问题或者发现程序有BUG和意见,可以在issues中提交  