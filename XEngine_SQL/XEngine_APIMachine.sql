/*
 Navicat Premium Data Transfer

 Source Server         : QCloud
 Source Server Type    : MySQL
 Source Server Version : 80036 (8.0.36-0ubuntu0.22.04.1)
 Source Host           : 43.139.170.67:3306
 Source Schema         : XEngine_APIMachine

 Target Server Type    : MySQL
 Target Server Version : 80036 (8.0.36-0ubuntu0.22.04.1)
 File Encoding         : 65001

 Date: 29/04/2024 10:51:26
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for XEngine_MachineList
-- ----------------------------
DROP TABLE IF EXISTS `XEngine_MachineList`;
CREATE TABLE `XEngine_MachineList`  (
  `ID` int NOT NULL AUTO_INCREMENT COMMENT 'ID',
  `tszServiceName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL DEFAULT NULL COMMENT '服务名称',
  `tszMachineName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '机器名称',
  `tszMachineCode` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '机器序列',
  `tszMachineSystem` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '系统名称',
  `tszMachineText` varchar(2048) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL DEFAULT NULL COMMENT '机器信息',
  `nTimeNumber` bigint NOT NULL COMMENT '启动次数',
  `tszCreateTime` datetime NOT NULL COMMENT '注册时间',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 4 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = DYNAMIC;

SET FOREIGN_KEY_CHECKS = 1;
