#pragma once
#include <iostream>
#include <cstring>

const std::string DB_ADDRESS = "127.0.0.1";
const int DB_PORT = 8689;
const std::string DB_LOGIN = "root";
const std::string DB_PASS = "password";
const std::string SCHEMA = "ATT_MGMT";

const std::string SUPERUSER_PASS = "1783174";
const int SUPERUSER_PASS_INT = std::stoi(SUPERUSER_PASS) ;