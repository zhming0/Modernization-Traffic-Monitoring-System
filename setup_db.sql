/*
 Navicat Premium Data Transfer

 Source Server         : SqliteConnection
 Source Server Type    : SQLite
 Source Server Version : 3007004
 Source Database       : main

 Target Server Type    : SQLite
 Target Server Version : 3007004
 File Encoding         : utf-8

 Date: 06/27/2012 21:01:30 PM
*/

PRAGMA foreign_keys = false;

-- ----------------------------
--  Table structure for "_images_old_20120627"
-- ----------------------------
DROP TABLE IF EXISTS "_images_old_20120627";
CREATE TABLE "_images_old_20120627" (
	 "name" text NOT NULL,
	 "status" integer NOT NULL DEFAULT 0,
	PRIMARY KEY("name")
);

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
--  Records of "admin"
-- ----------------------------
BEGIN;
INSERT INTO "admin" VALUES ('admin', 'admin');
INSERT INTO "admin" VALUES ('a', 'b');
COMMIT;

-- ----------------------------
--  Table structure for "car"
-- ----------------------------
DROP TABLE IF EXISTS "car";
CREATE TABLE "car" (
	 "carid" text(32,0) NOT NULL,
	 "owner" text(32,0) NOT NULL,
	 "violation" integer(8,0) DEFAULT 0,
	PRIMARY KEY("carid")
);

-- ----------------------------
--  Table structure for "images"
-- ----------------------------
DROP TABLE IF EXISTS "images";
CREATE TABLE "images" (
	 "name" text(32,0) NOT NULL,
	 "status" integer NOT NULL DEFAULT 0,
	 "path" text(96,0) NOT NULL,
	PRIMARY KEY("name")
);

PRAGMA foreign_keys = true;
