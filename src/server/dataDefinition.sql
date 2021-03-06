-- Set timezone to GMT +08:00 (Kuala Lumpur / Singapore)
SET time_zone = '+08:00';

-- Drop database if database exists
DROP DATABASE IF EXISTS `ATT_MGMT`;
CREATE DATABASE IF NOT EXISTS `ATT_MGMT` CHARACTER SET utf8mb4;

-- Select database after it is created
USE ATT_MGMT;

-- Drop table if exists
SET FOREIGN_KEY_CHECKS = 0;
DROP TABLE IF EXISTS `USER`;
DROP TABLE IF EXISTS `MEMBER`;
DROP TABLE IF EXISTS `ATTENDANCE`;
DROP TABLE IF EXISTS `ACTIVITY`;

-- Create tables
CREATE TABLE `USER` (
    `userID` INT AUTO_INCREMENT NOT NULL,
    `memberID` INT NOT NULL,
    `pw` TINYTEXT NOT NULL,
    `salt` TINYTEXT NOT NULL,
    `createTime` TIMESTAMP 
        DEFAULT CURRENT_TIMESTAMP NOT NULL,
    `pwUpdate` TIMESTAMP
        DEFAULT CURRENT_TIMESTAMP
        ON UPDATE CURRENT_TIMESTAMP 
        NOT NULL,
    PRIMARY KEY (`userID`),
    UNIQUE (`userID`)
);

CREATE TABLE `MEMBER` (
    `memberID` INT AUTO_INCREMENT NOT NULL,
    `engName` TINYTEXT NOT NULL,
    `matrixNo` CHAR(10) NOT NULL,
    `signupTime` TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,
    `updateTime` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP NOT NULL,
    `hostel` TINYTEXT,
    PRIMARY KEY (`memberID`),
    UNIQUE (`memberID`),
    UNIQUE (`matrixNo`)
);

CREATE TABLE `ATTENDANCE` (
    `attendanceID` INT AUTO_INCREMENT NOT NULL,
    `memberID` INT NOT NULL,
    `userID` INT NOT NULL,
    `activityID` INT NOT NULL,
    `createTime` TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,
    PRIMARY KEY (`attendanceID`),
    UNIQUE (`attendanceID`),
    UNIQUE (`memberID`)
);

CREATE TABLE `ACTIVITY` (
    `activityID` INT AUTO_INCREMENT NOT NULL,
    `activityName` VARCHAR(100) NOT NULL,
    `activityDesc` TEXT,
    `userID` INT NOT NULL,
    `activityYear` INT NOT NULL,
    `activityMonth` INT NOT NULL,
    `activityDay` INT NOT NULL,
    `activityHour` INT NOT NULL,
    `activityMinute` INT NOT NULL,
    `activityLocation` TEXT NOT NULL,
    `createTime` TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,
    `updateTime` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP NOT NULL,
    PRIMARY KEY (`activityID`),
    UNIQUE (`activityID`),
    UNIQUE (`activityName`)
);

-- Assigning foreign keys to tables and linking them up
ALTER TABLE `USER` ADD FOREIGN KEY (`memberID`) REFERENCES `MEMBER`(`memberID`);
ALTER TABLE `ATTENDANCE` ADD FOREIGN KEY (`memberID`) REFERENCES `MEMBER`(`memberID`);
ALTER TABLE `ATTENDANCE` ADD FOREIGN KEY (`userID`) REFERENCES `USER`(`userID`);
ALTER TABLE `ATTENDANCE` ADD FOREIGN KEY (`activityID`) REFERENCES `ACTIVITY`(`activityID`);
ALTER TABLE `ACTIVITY` ADD FOREIGN KEY (`userID`) REFERENCES `USER`(`userID`);