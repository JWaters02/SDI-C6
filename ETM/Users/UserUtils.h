//
// Created by bobby on 08/01/2022.
//

#ifndef ETM_USERUTILS_H
#define ETM_USERUTILS_H

#include <iostream>

enum class EUserTypes {
    CARGO_OWNER,
    DRIVER,
    COURIER,
    CONSIGNEE,
    FORWARDER,
    ADMIN,
    NONE
};

struct UserTypes {
    const std::string CargoOwner = "CargoOwner";
    const std::string Forwarder = "Forwarder";
    const std::string Driver = "Driver";
    const std::string Consignee = "Consignee";
    const std::string Admin = "Admin";
    const std::string Courier = "Courier";
};

struct LoginInfo {
    std::string username = "";
    std::string password;
};

struct SignupInfo {
    std::string username;
    std::string password;
    std::string email;
    std::string firstName;
    std::string lastName;
    int age;
    std::string phone;
    std::string homeAddress;
    std::string homeCity;
    // Types are: CargoOwner, Driver, Courier, Consignee, Forwarder
    // Not using an enum because converting them to string is a pain in C++
    std::string type;
};

struct DriverSignupInfo {
    std::string NINumber;
    std::string drivingLicenceID;
    std::string lorryType;
    std::string lorryReg;
    std::string companyAddress;
    std::string companyCity;
};

struct CargoOwnerSignupInfo {
    std::string goodsCategory;
};

struct CourierSignupInfo {
    std::string companyName;
    std::string companyPhone;
    std::string companyAddress;
    std::string companyCity;
};

struct ForwarderSignupInfo {
    std::string companyName;
    std::string companyPhone;
    std::string companyAddress;
    std::string companyCity;
};

// Remember, lengths are 1 less than the actual minimum
struct InfoMinLengths {
    const int USERNAME = 2;
    const int PASSWORD = 0;
    const int EMAIL = 2;
    const int FIRSTNAME = 2;
    const int LASTNAME = 2;
    const int AGE = 17;
    const int PHONE = 9;
    const int HOME_ADDRESS = 2;
    const int HOME_CITY = 2;
    const int COMPANY_NAME = 2;
    const int COMPANY_PHONE = 9;
    const int COMPANY_ADDRESS = 2;
    const int COMPANY_CITY = 2;
    const int NI_NUMBER = 8;
    const int DRIVING_LICENCE_ID = 15;
    const int LORRY_TYPE = 1;
    const int LORRY_REG = 3;
    const int GOODS_CATEGORY = 1;
};

class UserUtils {

};

#endif //ETM_USERUTILS_H
