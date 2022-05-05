//
// Created by bobby on 08/01/2022.
//

#ifndef ETM_LOGIN_H
#define ETM_LOGIN_H

#include "BCrypt.hpp"
#include "Users/UserUtils.h"
#include "Database/DBHandler.h"
#include "RegistrationCheck.h"

enum class ErrorTypes {
    INVALID_LOGIN,
    USERNAME_ALREADY_EXISTS,
    NOT_ALL_FIELDS_FILLED,
    USERNAME_NOT_FOUND,
    NO_USERTYPE_SELECTED,
    PASSWORDS_DO_NOT_MATCH,
    EMPTY_USERNAME,
    SUCCESS
};

class Login {
private:
    static InfoMinLengths MINS;

public:
    static ErrorTypes isValidLogin(const LoginInfo& loginInfo);
    static ErrorTypes isValidSignup(const SignupInfo& signupInfo);
    static bool isValidDriverSignup(const DriverSignupInfo& signupInfo);
    static bool isValidCourierSignup(const CourierSignupInfo& signupInfo);
    static bool isValidForwarderSignup(const ForwarderSignupInfo& signupInfo);
    static bool isValidCargoOwnerSignup(const CargoOwnerSignupInfo& signupInfo);

    static void storeSignupDetails(const SignupInfo& signupInfo);
    static void storeDriverSignupDetails(const SignupInfo& username, const DriverSignupInfo& signupInfo);
    static void storeCourierSignupDetails(const SignupInfo& username, const CourierSignupInfo& signupInfo);
    static void storeForwarderSignupDetails(const SignupInfo& username, const ForwarderSignupInfo& signupInfo);
    static void storeCargoOwnerSignupDetails(const SignupInfo& username, const CargoOwnerSignupInfo& signupInfo);

    static EUserTypes getUserType(const LoginInfo& loginInfo);
};


#endif //ETM_LOGIN_H
