-- phpMyAdmin SQL Dump
-- version 4.7.4
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Dec 20, 2017 at 12:20 AM
-- Server version: 5.7.19
-- PHP Version: 5.6.31

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `ransom`
--
CREATE DATABASE IF NOT EXISTS `ransom`;
use `ransom`
-- --------------------------------------------------------

--
-- Table structure for table `db_keys`
--

DROP TABLE IF EXISTS `db_keys`;
CREATE TABLE IF NOT EXISTS `db_keys` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `private_key` longtext NOT NULL,
  `public_key` longtext NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `db_keys`
--

INSERT INTO `db_keys` (`id`, `private_key`, `public_key`) VALUES
(4, '-----BEGIN RSA PRIVATE KEY-----\r\nMIICXQIBAAKBgQD+0ByQdaNtHNxe+W5XGlb63+jdP+hn6bj+XdV287WDWPDRXfR8\r\nXLnSAij336E8gbUM2+qyBtDqKwf5/MZeObDnpXTI70PLDBXvPaIBh5OcTggywo69\r\nbGd/NAkX0ZyJv35vlqcJNatCgXI+YCjcpuhoxSCyVvXBW2LCKRmTUaURSwIDAQAB\r\nAoGAJJk1kRYka/aaPFXtIDubRJtGcgjM06gBNx+5GkW0y3HJ3Ph2tioHUn+W7MtE\r\n+FDU9Uzc78cE2K1njuNchooYu1NtHnWvm/ZXe3xS7hefIwGy0IzUD5y+rv3aOQQ0\r\njdmqKuMPauTJHdNZeJICvhSOxMpVDOIx2YGDqFMt0RNN9xkCQQD/cg1df4yZIAG1\r\nWguGdv+iudBqmfr9oM0c36ZAOcsicEnETsNn0QTW6LLnXp4dzbF4I1k8B3uqBNXR\r\nXdNKxVEPAkEA/121NfMV9HU9Mip3/P+2WNn6BxyXHTS9VdEPDQFTUVAOkAEi9b/X\r\n/kRb+UjeTnIdqlUGA3C25tSj12qypJXEBQJAVIyvl87r/pL1fc08G1mv63CNZ3tn\r\n9CMRQQlVwdRfRBrej7dyPh6U9302GhbbRwoaP6WTl6bya6gGDbJ8iTceSQJBAIDA\r\nq4P2+yPVFLS9at/5weOMi56YUKyeEbQ6At+owmxl8+GxYQIM5wdBSionDkb5DHH8\r\nClsjsmQx5CXRmx6WkE0CQQCq28HF+S+HaTI4fcFQIK8xpiKus5RxQSCw520tFf+N\r\njvhtfkRR4d4oR6boiA1ymlozoglPv+rcKQY194pRG5QD\r\n-----END RSA PRIVATE KEY-----', '-----BEGIN PUBLIC KEY-----\r\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQD+0ByQdaNtHNxe+W5XGlb63+jd\r\nP+hn6bj+XdV287WDWPDRXfR8XLnSAij336E8gbUM2+qyBtDqKwf5/MZeObDnpXTI\r\n70PLDBXvPaIBh5OcTggywo69bGd/NAkX0ZyJv35vlqcJNatCgXI+YCjcpuhoxSCy\r\nVvXBW2LCKRmTUaURSwIDAQAB\r\n-----END PUBLIC KEY-----');

-- --------------------------------------------------------

--
-- Table structure for table `infos`
--

DROP TABLE IF EXISTS `infos`;
CREATE TABLE IF NOT EXISTS `infos` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `machineName` varchar(255) DEFAULT NULL,
  `ipAddress` varchar(255) DEFAULT NULL,
  `publicKey` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `infos`
--

INSERT INTO `infos` (`id`, `machineName`, `ipAddress`, `publicKey`) VALUES
(1, 'pc de jean', '192.168.0.1', 'PIYFGEPUIYVFGPE'),
(2, 'pc de paul', '192.168.0.2', 'EUBVEUYHVE'),
(3, 'pc de Michel', '10.10.0.1', 'UHJGCEIOUSJFGPE'),
(4, 'Iphone de paul', '192.168.0.4', 'BVOURGHVOEUF');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
