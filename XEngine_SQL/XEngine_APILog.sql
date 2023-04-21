/*
 Navicat Premium Data Transfer

 Source Server         : Test
 Source Server Type    : MySQL
 Source Server Version : 80031 (8.0.31-0ubuntu0.20.04.2)
 Source Host           : 192.168.1.10:3306
 Source Schema         : XEngine_APILog

 Target Server Type    : MySQL
 Target Server Version : 80031 (8.0.31-0ubuntu0.20.04.2)
 File Encoding         : 65001

 Date: 11/01/2023 17:21:51
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for XLogTemplate
-- ----------------------------
DROP TABLE IF EXISTS `XLogTemplate`;
CREATE TABLE `XLogTemplate`  (
  `ID` int NOT NULL AUTO_INCREMENT,
  `tszFileName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL DEFAULT NULL COMMENT '文件名',
  `tszFuncName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL DEFAULT NULL COMMENT '函数名',
  `nLogLine` int NULL DEFAULT NULL COMMENT '第几行',
  `nLogLevel` int NULL DEFAULT NULL COMMENT '打印级别',
  `tszLogBuffer` varchar(8196) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '日志信息',
  `tszLogTime` datetime NOT NULL COMMENT '日志时间',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
