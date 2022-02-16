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
    if (signupInfo.username.length() > MINS.USERNAME &&
        signupInfo.password.length() > MINS.PASSWORD &&
        signupInfo.email.length() > MINS.EMAIL &&
        signupInfo.email.find('@') &&
        signupInfo.firstName.length() > MINS.FIRSTNAME &&
        signupInfo.lastName.length() > MINS.LASTNAME &&
        signupInfo.phone.length() > MINS.PHONE &&
        std::to_string(signupInfo.age).length() > 0 &&
        signupInfo.age > MINS.AGE &&
        signupInfo.homeAddress.length() > MINS.HOME_ADDRESS &&
        signupInfo.homeCity.length() > MINS.HOME_CITY)
        return true;
    return false;
}

bool Login::validateDriverSignup(const DriverSignupInfo &signupInfo) {
    if (std::to_string(signupInfo.NINumber).length() > MINS.NI_NUMBER &&
        signupInfo.drivingLicenceID.length() > MINS.DRIVING_LICENCE_ID &&
        signupInfo.lorryType.length() > MINS.LORRY_TYPE &&
        signupInfo.companyCity.length() > MINS.COMPANY_CITY &&
        signupInfo.companyAddress.length() > MINS.COMPANY_ADDRESS)
        return true;
    return false;
}

bool Login::validateCourierSignup(const CourierSignupInfo &signupInfo) {
    if (signupInfo.companyName.length() > MINS.COMPANY_NAME &&
        signupInfo.companyPhone.length() > MINS.COMPANY_PHONE &&
        signupInfo.companyAddress.length() > MINS.COMPANY_CITY &&
        signupInfo.companyCity.length() > MINS.COMPANY_CITY)
        return true;
    return false;
}

bool Login::validateForwarderSignup(const ForwarderSignupInfo &signupInfo) {
    if (signupInfo.companyName.length() > MINS.COMPANY_NAME &&
        signupInfo.companyPhone.length() > MINS.COMPANY_PHONE &&
        signupInfo.companyAddress.length() > MINS.COMPANY_CITY &&
        signupInfo.companyCity.length() > MINS.COMPANY_CITY)
        return true;
    return false;
}

bool Login::validateCargoOwnerSignup(const CargoOwnerSignupInfo &signupInfo) {
    if (signupInfo.goodsCategory.length() > MINS.GOODS_CATEGORY) return true;
    return false;
}
