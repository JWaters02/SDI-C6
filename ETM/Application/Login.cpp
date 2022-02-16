//
// Created by bobby on 08/01/2022.
//

#include "Login.h"

InfoMinLengths Login::MINS;

bool Login::isValidLogin(const LoginInfo &loginInfo) {
    if (loginInfo.username.length() > MINS.USERNAME && loginInfo.password.length() > MINS.PASSWORD) {
        // If username already exist in the database
        if (!DBHandler::getResult("SELECT * FROM Users WHERE username = '" + loginInfo.username + "'").empty()) {
            // If hash in DB is equal to hash of current password, return true (as passwords match)
            return BCrypt::validatePassword(loginInfo.password,
                                            DBHandler::getResult(
                                                    "SELECT password FROM Users WHERE password = '" +
                                                    loginInfo.password + "'"));
        }
    }
    return false;
}

bool Login::isValidSignup(const SignupInfo &signupInfo) {
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

bool Login::isValidDriverSignup(const DriverSignupInfo &signupInfo) {
    if (signupInfo.NINumber.length() > MINS.NI_NUMBER &&
        signupInfo.drivingLicenceID.length() > MINS.DRIVING_LICENCE_ID &&
        signupInfo.lorryType.length() > MINS.LORRY_TYPE &&
        signupInfo.companyCity.length() > MINS.COMPANY_CITY &&
        signupInfo.companyAddress.length() > MINS.COMPANY_ADDRESS)
        return true;
    return false;
}

bool Login::isValidCourierSignup(const CourierSignupInfo &signupInfo) {
    if (signupInfo.companyName.length() > MINS.COMPANY_NAME &&
        signupInfo.companyPhone.length() > MINS.COMPANY_PHONE &&
        signupInfo.companyAddress.length() > MINS.COMPANY_CITY &&
        signupInfo.companyCity.length() > MINS.COMPANY_CITY)
        return true;
    return false;
}

bool Login::isValidForwarderSignup(const ForwarderSignupInfo &signupInfo) {
    if (signupInfo.companyName.length() > MINS.COMPANY_NAME &&
        signupInfo.companyPhone.length() > MINS.COMPANY_PHONE &&
        signupInfo.companyAddress.length() > MINS.COMPANY_CITY &&
        signupInfo.companyCity.length() > MINS.COMPANY_CITY)
        return true;
    return false;
}

bool Login::isValidCargoOwnerSignup(const CargoOwnerSignupInfo &signupInfo) {
    if (signupInfo.goodsCategory.length() > MINS.GOODS_CATEGORY) return true;
    return false;
}

void Login::storeSignupDetails(const SignupInfo &signupInfo) {
    std::stringstream query;
    query   << "INSERT INTO Users VALUES ('"
            << signupInfo.firstName << "', '"
            << signupInfo.lastName << "', "
            << signupInfo.age << ", '"
            << signupInfo.email << "', '"
            << signupInfo.username << "', '"
            << BCrypt::generateHash(signupInfo.password) << "', '"
            << signupInfo.phone << "', '"
            << signupInfo.homeAddress << "', '"
            << signupInfo.homeCity << "', '"
            << signupInfo.type << "');";
    DBHandler::writeFields(query.str());
}

void Login::storeDriverSignupDetails(const SignupInfo& username, const DriverSignupInfo &signupInfo) {
    std::stringstream query;
    query   << "INSERT INTO Drivers VALUES ('"
            << username.username << "', '"
            << signupInfo.NINumber << "', '"
            << signupInfo.drivingLicenceID << "', '"
            << signupInfo.lorryType << "', '"
            << signupInfo.companyCity << "', '"
            << signupInfo.companyAddress << "');";
    DBHandler::writeFields(query.str());
}

void Login::storeCourierSignupDetails(const SignupInfo& username, const CourierSignupInfo &signupInfo) {
    std::stringstream query;
    query   << "INSERT INTO Couriers VALUES ('"
            << username.username << "', '"
            << signupInfo.companyName << "', '"
            << signupInfo.companyPhone << "', '"
            << signupInfo.companyAddress << "', '"
            << signupInfo.companyCity << "');";
    DBHandler::writeFields(query.str());
}

void Login::storeForwarderSignupDetails(const SignupInfo& username, const ForwarderSignupInfo &signupInfo) {
    std::stringstream query;
    query   << "INSERT INTO Forwarders VALUES ('"
            << username.username << "', '"
            << signupInfo.companyName << "', '"
            << signupInfo.companyPhone << "', '"
            << signupInfo.companyAddress << "', '"
            << signupInfo.companyCity << "');";
    DBHandler::writeFields(query.str());
}

void Login::storeCargoOwnerSignupDetails(const SignupInfo& username, const CargoOwnerSignupInfo &signupInfo) {
    std::stringstream query;
    query   << "INSERT INTO CargoOwners VALUES ('"
            << username.username << "', '"
            << signupInfo.goodsCategory << "');";
    DBHandler::writeFields(query.str());
}
