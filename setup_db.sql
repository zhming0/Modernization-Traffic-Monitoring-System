/*
 Navicat Premium Data Transfer

 Source Server         : SqliteConnection
 Source Server Type    : SQLite
 Source Server Version : 3007004
 Source Database       : main

 Target Server Type    : SQLite
 Target Server Version : 3007004
 File Encoding         : utf-8

 Date: 06/26/2012 16:35:41 PM
*/

PRAGMA foreign_keys = false;

-- ----------------------------
--  Table structure for "admin"
-- ----------------------------
DROP TABLE IF EXISTS "admin";
CREATE TABLE "admin" (
	 "username" text(32,0) NOT NULL,
	 "password" text(32,0) NOT NULL,
	PRIMARY KEY("username")
);

-- ----------------------------
--  Table structure for "car"
-- ----------------------------
DROP TABLE IF EXISTS "car";
CREATE TABLE "car" (
	 "carid" text(32,0) NOT NULL,
	 "owner" text(32,0) NOT NULL,
	PRIMARY KEY("carid")
);

PRAGMA foreign_keys = true;
