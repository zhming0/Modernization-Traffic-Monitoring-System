/*
 Navicat Premium Data Transfer

 Source Server         : SqliteConnection
 Source Server Type    : SQLite
 Source Server Version : 3007004
 Source Database       : main

 Target Server Type    : SQLite
 Target Server Version : 3007004
 File Encoding         : utf-8

 Date: 07/13/2012 17:01:33 PM
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
	 "rec_result" text(10,0),
	PRIMARY KEY("name")
);

PRAGMA foreign_keys = true;
