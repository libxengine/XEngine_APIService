/*
 Navicat Premium Data Transfer

 Source Server         : QCloud
 Source Server Type    : MySQL
 Source Server Version : 80032 (8.0.32-0ubuntu0.22.04.2)
 Source Host           : 42.194.178.57:3306
 Source Schema         : XEngine_APISLink

 Target Server Type    : MySQL
 Target Server Version : 80032 (8.0.32-0ubuntu0.22.04.2)
 File Encoding         : 65001

 Date: 11/04/2023 13:54:53
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for XEngine_ShortLink
-- ----------------------------
DROP TABLE IF EXISTS `XEngine_ShortLink`;
CREATE TABLE `XEngine_ShortLink`  (
  `ID` int NOT NULL AUTO_INCREMENT COMMENT 'ID',
  `tszFullUrl` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '要映射的URL',
  `tszShortUrl` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '短连接URL',
  `tszKeyUrl` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT 'URLKey',
  `tszMapUrl` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '映射到的地址',
  `tszCreateTime` datetime NOT NULL COMMENT '创建的时间',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 7 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
