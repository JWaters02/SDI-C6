//
// Created by bobby on 08/01/2022.
//

#ifndef ETM_LOGIN_H
#define ETM_LOGIN_H

#include "Users/UserUtils.h"
#include "Database/DBHandler.h"

class Login {
private:
    static InfoMinLengths MINS;

public:
    static bool validateLogin(const LoginInfo& loginInfo);
    static bool validateSignup(const SignupInfo& signupInfo);
};


#endif //ETM_LOGIN_H
