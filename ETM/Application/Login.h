//
// Created by bobby on 08/01/2022.
//

#ifndef ETM_LOGIN_H
#define ETM_LOGIN_H

#include "bcrypt/BCrypt.hpp"
#include "Users/UserUtils.h"
#include "Database/DBHandler.h"

class Login {
private:
    static InfoMinLengths MINS;

public:
    static bool isValidLogin(const LoginInfo& loginInfo);
    static bool isValidSignup(const SignupInfo& signupInfo);
    static bool isValidDriverSignup(const DriverSignupInfo& signupInfo);
    static bool isValidCourierSignup(const CourierSignupInfo& signupInfo);
    static bool isValidForwarderSignup(const ForwarderSignupInfo& signupInfo);
    static bool isValidCargoOwnerSignup(const CargoOwnerSignupInfo& signupInfo);

    static void storeSignupDetails(const SignupInfo& signupInfo);
    static void storeDriverSignupDetails(const SignupInfo& username, const DriverSignupInfo& signupInfo);
    static void storeCourierSignupDetails(const SignupInfo& username, const CourierSignupInfo& signupInfo);
    static void storeForwarderSignupDetails(const SignupInfo& username, const ForwarderSignupInfo& signupInfo);
    static void storeCargoOwnerSignupDetails(const SignupInfo& username, const CargoOwnerSignupInfo& signupInfo);
};


#endif //ETM_LOGIN_H
