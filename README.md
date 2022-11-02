[中文](README.md) ||  [English](README.en.md)  
# XEngine_APIService
本仓库有开发和主分支,如果要使用,请使用master分支下的代码  
只要仓库不是在暂停状态,那么就会有人一直维护和开发,请放心使用  

## 介绍
c c++ 接口服务器  
c c++ interface api service  
这是一个信息查询的API接口服务,目前市面上的信息查询服务都需要收费,而我们这个信息查询服务属于免费开源的.  
这个服务主要使用HTTP/V1.1实现各种接口服务.  
这是一个不包含任何语言属性的通用信息查询服务.  
你可以使用此代码实现自己的信息查询服务,支持查询任何信息  
基于libXEngine开发并实现的一套简洁高性能跨平台接口服务  
并且支持模块插件  

#### 为什么选择我们
支持私有化部署,免费,安全.开源,可控


## 软件特性
1. 权限验证
2. 支持IP地址位置信息查询(IPV4和IPV6)
3. 支持身份证校验与信息查询
4. 支持手机号信息归属查询
5. 天气预报(计划中)
6. 农历公历转换(计划中)
7. 新闻头条(计划中)
8. 标准身高体重
9. 生肖星座
10. 密码生成器
11. 世界时区
12. 油价查询(计划中)
13. 行政邮编
14. 银行卡验证
15. 汇率计算(计划中)
16. 二维码生成解析(计划中)
17. 简繁转换
18. 二十四节气(计划中)
19. 新华词典
20. 计量转换
21. CDKey创建支持
22. 分布式锁API
23. 短连接生成
24. 本地标准时间

## 安装教程

#### XEngine环境
必须安装XEngine,版本需要V7.38或者以上版本,安装XEngine可以参考其Readme文档  
GITEE:https://gitee.com/xyry/libxengine  
GITHUB:https://github.com/libxengine/xengine

###### 快速部署
git clone https://gitee.com/xyry/libxengine.git 或者 git clone https://github.com/libxengine/xengine.git  
window执行XEngine_WINEnv.bat 脚本.  
Linux执行:sudo ./XEngine_LINEnv.sh -i 3  
macos执行:./XEngine_LINEnv.sh -i 3  

#### Windows
使用VS打开并且编译,支持WINDOWS 7SP1以上系统  
直接运行即可

#### Linux
安装opencc,ubuntu:sudo apt install libopencc-dev  
centos:需要自己编译  
Linux使用Makefile编译,UBUNTU20.04 x64或者CENTOS8 x64  
在控制台运行

#### Macos
安装opencc,执行命令:brew install opencc  
使用makefile编译,控制台运行,需要mac 12以及以上版本  
在控制台运行

##### 编译命令
在XEngine_Source目录下执行命令  
make 编译  
make FLAGS=InstallAll 安装库程序  
make FLAGS=CleanAll 清理编译  

#### 插件使用
你可以参考XEngine_PluginModule 下面的项目来编写插件  
编写好的插件需要通过JSON配置才能启用  

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
更多内容请参考文档  
手机信息查询  
接口:http://app.xyry.org:5501/api?function=phone&params1=13699439999
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
接口:http://app.xyry.org:5501/api?function=ip&params1=1.29.164.255
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
接口:http://app.xyry.org:5501/api?function=id&params1=511025198800000000
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
银行卡验证  
接口:http://app.xyry.org:5501/api?function=bank&params1=6214832830000000
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
语言转换  
接口:http://app.xyry.org:5501/api?function=language&params1=简体到繁体&params2=1
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
翻译  
接口:http://app.xyry.org:5501/api?function=translation&params1=中国&params2=0
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
CDKey授权  
接口:http://app.xyry.org:5501/api?function=cdkey&params1=0
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
分布式锁  
接口:http://app.xyry.org:5501/api?function=lock&params1=1000154321&params2=1
```json
{
    "code":0,
    "data":{
        "xhToken":1000154321
    },
    "msg":"success"
}
```
## 参与贡献
希望大家多多提交代码参与贡献  

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request  

## 关注我们
如果你觉得这个软件对你有帮助,请你给我们一个START吧

## 提交问题

如果你有问题或者发现程序有BUG和意见,可以在issues中提交  