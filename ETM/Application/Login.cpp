//
// Created by bobby on 08/01/2022.
//

#include "Login.h"

InfoMinLengths Login::MINS;

bool Login::validateLogin(const LoginInfo& loginInfo) {
    // Remember password is hashed so any length more than 0 is valid
    if (loginInfo.username.length() > MINS.USERNAME && loginInfo.password.length() > MINS.PASSWORD) {
        return true;
    }
    // If any details already exist in the database, return true
    if (!DBHandler::getResult("SELECT * FROM users WHERE username = '" + loginInfo.username + "'").empty() &&
        !DBHandler::getResult("SELECT * FROM users WHERE password = '" + loginInfo.password + "'").empty()) {
        return true;
    }

    return false;
}

bool Login::validateSignup(const SignupInfo& signupInfo) {
    if (signupInfo.username.length() > MINS.USERNAME && signupInfo.password.length() > MINS.PASSWORD &&
        signupInfo.email.length() > MINS.EMAIL && signupInfo.email.find('@') &&
        signupInfo.firstName.length() > MINS.FIRSTNAME && signupInfo.lastName.length() > MINS.LASTNAME &&
        signupInfo.phone.length() > MINS.PHONE && std::to_string(signupInfo.age).length() > 0 &&
        signupInfo.age > MINS.AGE && signupInfo.home_address.length() > MINS.HOME_ADDRESS &&
        signupInfo.home_city.length() > MINS.HOME_CITY && signupInfo.business_address.length() > MINS.BUSINESS_ADDRESS &&
        signupInfo.business_city.length() > MINS.BUSINESS_CITY && signupInfo.country.length() > MINS.COUNTRY) {
        return true;
    }
    return false;
}
