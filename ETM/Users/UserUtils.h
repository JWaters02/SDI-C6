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

struct InfoMinLengths {
    const int USERNAME = 5;
    const int PASSWORD = 0;
    const int EMAIL = 2;
    const int FIRSTNAME = 2;
    const int LASTNAME = 2;
    const int AGE = 18;
    const int PHONE = 9;
    const int HOME_ADDRESS = 5;
    const int HOME_CITY = 2;
    const int BUSINESS_ADDRESS = 5;
    const int BUSINESS_CITY = 2;
    const int COUNTRY = 2;
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
