//
// Created by bobby on 08/01/2022.
//

#ifndef ETM_USERUTILS_H
#define ETM_USERUTILS_H

#include <iostream>

struct LoginInfo {
    std::string username;
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
    std::string home_address;
    std::string home_city;
    std::string business_address;
    std::string business_city;
    std::string country;
};

struct DriverSignupInfo {
    int NINumber;
    std::string drivingLicenceID;
    std::string lorryType;
};

enum SignupTypes {
    Username,
    Password,
    ConfirmPassword,
    Email,
    FirstName,
    LastName,
    Age,
    Phone,
    HomeAddress,
    HomeCity,
    BusinessAddress,
    BusinessCity,
    Country,
    NINumber,
    DrivingLicenceID,
    LorryType
};

enum UserTypes {
    CargoOwner,
    Driver,
    TransportationCompany
};

class UserUtils {
public:

};

#endif //ETM_USERUTILS_H
