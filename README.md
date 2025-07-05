[中文](README.md) ||  [English](README.en.md)  
# XEngine_APIService
本仓库有开发和主分支,如果要使用,请使用master分支下的代码  
只要仓库不是在暂停状态,那么就会有人一直维护和开发,请放心使用  

## 介绍
c c++ 接口服务器  
c c++ interface api service  
这是一个信息查询的API接口服务,目前市面上的信息查询服务都需要收费,而我们这个信息查询服务属于免费开源的.  
或者说他不光是一个查询服务,他还可以提供机器管理进程守护等功能  
这个服务主要使用HTTP/V1.1实现各种接口服务.  
这是一个不包含任何语言属性的通用信息查询服务.  
你可以使用此代码实现自己的信息查询服务,支持查询任何信息  
基于libXEngine开发并实现的一套简洁高性能跨平台接口服务  
并且支持插件系统,dll(so,dylib)模块或者lua脚本  

## 注意
编译发布版本将只在github上面发布.

#### 为什么选择我们
支持私有化部署,免费,安全.开源,可控  
几十种信息查询完全免费开源,而同类型产品全是收费API计数收费  
支持三方接口数据缓存.可以节约你的其他查询信息费用  
可以让你一年节约90%信息服务费用.  

## 软件特性
1. 权限验证
2. 支持IP地址位置信息查询
3. 支持身份证校验与信息查询
4. 支持手机号信息归属查询
5. 天气预报
6. 农历公历转换(计划中)
7. 新闻头条(计划中)
8. 标准身高体重
9. 生肖星座
10. 密码生成器
11. 世界时区
12. 油价查询
13. 行政邮编
14. 银行卡验证
15. 汇率计算(计划中)
16. 二维码生成解析
17. 二十四节气(计划中)
18. 翻译
19. 计量转换
20. 网络测试
21. 分布式锁API
22. 短连接生成和转发
23. 本地标准时间
24. 数学计算
25. 日志服务
26. 插件脚本热重载
27. 敏感词检测
28. 远程控制(后台管理)
29. 图像处理
30. 进程守护
31. 行政区域ID转换
32. 机器信息收集
33. 心跳处理
34. STUN NAT协议
35. NTP时间同步协议
36. 支持MAC地址厂商查询
37. ORC图像文本提取
38. P2P

## 安装教程

#### XEngine环境
必须安装XEngine,版本需要V9.x或者以上版本,安装XEngine可以参考其Readme文档  
GITEE:https://gitee.com/libxengine/libxengine  
GITHUB:https://github.com/libxengine/libxengine

###### 快速部署
git clone https://gitee.com/libxengine/libxengine.git 或者 git clone https://github.com/libxengine/libxengine.git  
window执行XEngine_WINEnv.bat 脚本.  
Linux执行:sudo ./XEngine_LINEnv.sh -i 3  
macos执行:./XEngine_LINEnv.sh -i 3  

###### 开发环境搭建
建议使用github拉取代码,在使用VS2022+COPILOG组合.Copilot会自动帮你分析和修改代码  
为了节约资源,现在ip和phone,mac数据库需要自己拷贝.执行XEngine_Release/copydb.bat(copydb.sh)脚本即可.否则会报错

#### 数据库环境
需要MYSQL数据库8.0以上版本.通过CreateDatabase.sql创建表,然后导入剩余的表  
修改配置文件里面XSQL里面的数据库配置为你的  
默认配置没有开启数据库支持,如果需要数据库接口支持,需要自己开启数据库  

#### sub module
由于依赖的子模块,在你checkout仓库后,在仓库目录下执行下面的命令拉取子模块  
git submodule init  
git submodule update  
如果github访问失败,你也可以clone该项目,在主目录下使用命令:  
git clone https://gitee.com/xengine/XEngine_OPenSource.git XEngine_Source/XEngine_DependLibrary/XEngine_OPenSource
git clone https://gitee.com/xengine/XEngine_IPMacData.git XEngine_Source/XEngine_DependLibrary/XEngine_IPMacData  
git clone https://gitee.com/xengine/XEngine_PhoneData.git XEngine_Source/XEngine_DependLibrary/XEngine_PhoneData  

#### Windows
需要vcpkg配置第三方环境,具体参考vcpkg安装方式,安装好后执行:vcpkg.exe install lua:x86-windows opencv[contrib]:x86-windows libqrencode:x86-windows lua:x64-windows opencv[contrib]:x64-windows libqrencode:x64-windows  
使用VS打开并且编译,支持WINDOWS 7SP1以上系统  
直接运行即可

#### Linux
ubuntu:sudo apt install liblua5.4-dev libopencv-dev libopencv-contrib-dev libqrencode-dev libleptonica-dev libtesseract-dev -y  
centos:sudo dnf install lua-devel opencv-devel qrencode-devel leptonica-devel tesseract-devel -y  
Linux使用Makefile编译,UBUNTU24.04 x64或者RockyLinux 9 x64  
在控制台运行

#### Macos
安装环境,执行命令:brew install lua opencv qrencode leptonica tesseract  
使用makefile编译,控制台运行,需要mac 13以及以上版本  
在控制台运行

##### 编译命令
在XEngine_Source目录下执行命令  
make 编译  
make FLAGS=InstallAll 安装库程序  
make FLAGS=CleanAll 清理编译  

#### 插件使用
你可以参考XEngine_PluginModule 下面的项目来编写插件  
编写好的插件需要通过JSON配置才能启用  

## 系统任务列表
下载文件  
删除指定文件  
删除指定目录  
上传一个文件到指定FTP  
请求获取文件夹中的文件列表  
执行指定程序    
结束指定进程  
远程关闭计算机  
执行命令  
信息报告    

#### 使用说明

1.  切换到MASTER分支
2.  下载代码
3.  编译
4.  安装
5.  运行

## 目录结构
- XEngine_Docment    文档目录结构  
- XEngine_Release    安装目录结构  
- XEngine_Source     源代目录结构  
- XEngine_APPClient  客户端演示代码  

## 当前任务

## 其他问题  
你可以参考docment目录下的文档.里面包含了API协议和服务说明.

## 视频教程
你也可以观看视频教程来了解我们的代码框架情况:https://www.bilibili.com/video/BV13z421d7W8

## 测试服务器
地址:app.libxengine.com,端口:5501  

#### 测试接口示例
更多内容请参考文档  
身份证查询  
接口:http://app.libxengine.com:5501/api?function=id&params1=511025198800000000
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
接口:http://app.libxengine.com:5501/api?function=bank&params1=6214832830000000
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
翻译  
接口:http://127.0.0.1:5501/api?function=translation&msg=中文翻译成英文&src=1&dst=2
```json
{
    "code":0,
    "data":{
        "tszDestStr":"Translate from Chinese to English",
        "tszFromStr":"zh",
        "tszSourceStr":"中文翻译成英文",
        "tszToStr":"en"
    },
    "msg":"success"
}
```
分布式锁  
接口:http://app.libxengine.com:5501/api?function=lock&params1=1000154321&params2=1
```json
{
    "code":0,
    "data":{
        "xhToken":1000154321
    },
    "msg":"success"
}
```
行政邮编  
接口:http://app.libxengine.com:5501/api?function=zipcode&params1=0  
```json
{
    "nZipCode":100010
}
```
日志操作  
接口:http://app.libxengine.com:5501/api?function=log&params1=1  
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
油价查询  
接口:http://app.libxengine.com:5501/api?function=oil&addr=四川  
```json
{
    "code": 0,
    "data": {
        "dlValue0": 7.9100000000000001,
        "dlValue10": 8.3800000000000008,
        "dlValue20": 8.6899999999999995,
        "dlValue35": 0,
        "dlValue92": 8.2799999999999994,
        "dlValue95": 8.8499999999999996,
        "dlValue98": 9.6199999999999992,
        "tszCityStr": "四川",
        "tszUPTime": "2024-05-08 14:39:53"
    },
    "msg": "success"
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