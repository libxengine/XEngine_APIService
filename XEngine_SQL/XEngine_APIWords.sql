/*
 Navicat Premium Data Transfer

 Source Server         : mysql
 Source Server Type    : MySQL
 Source Server Version : 80033 (8.0.33-0ubuntu0.22.04.4)
 Source Host           : 10.0.3.155:3306
 Source Schema         : XEngine_APIWords

 Target Server Type    : MySQL
 Target Server Version : 80033 (8.0.33-0ubuntu0.22.04.4)
 File Encoding         : 65001

 Date: 09/08/2023 14:10:48
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for WordFilter
-- ----------------------------
DROP TABLE IF EXISTS `WordFilter`;
CREATE TABLE `WordFilter`  (
  `tszWordsFrom` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '替换源',
  `tszWordsTo` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL DEFAULT NULL COMMENT '替换目标',
  `nLevel` tinyint NULL DEFAULT NULL COMMENT '过滤级别'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
