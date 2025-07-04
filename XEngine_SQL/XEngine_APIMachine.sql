/*
 Navicat Premium Dump SQL

 Source Server         : QQCloud
 Source Server Type    : MySQL
 Source Server Version : 80042 (8.0.42-0ubuntu0.24.04.1)
 Source Host           : 118.25.14.242:3306
 Source Schema         : XEngine_APIMachine

 Target Server Type    : MySQL
 Target Server Version : 80042 (8.0.42-0ubuntu0.24.04.1)
 File Encoding         : 65001

 Date: 03/07/2025 14:49:40
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
  `tszMachineUser` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '机器用户',
  `tszMachineSystem` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '系统名称',
  `tszMachineSoftware` varchar(4096) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL DEFAULT NULL COMMENT '软件信息',
  `tszMachineHardware` varchar(4096) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL DEFAULT NULL COMMENT '硬件信息',
  `nTimeNumber` bigint NOT NULL COMMENT '启动次数',
  `tszLastTime` datetime NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
  `tszCreateTime` datetime NOT NULL COMMENT '注册时间',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 0 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = DYNAMIC;

SET FOREIGN_KEY_CHECKS = 1;
