//
// Created by bobby on 08/01/2022.
//

#include "Login.h"

InfoMinLengths Login::MINS;

/**
 * Check if the provided username and password are valid.
 * @param loginInfo The login information to check.
 * @return The type of error result (if none, return SUCCESS).
 */
ErrorTypes Login::isValidLogin(const LoginInfo &loginInfo) {
    if (loginInfo.username.empty()) {
        return ErrorTypes::EMPTY_USERNAME;
    }
    if (loginInfo.username.length() > MINS.USERNAME && loginInfo.password.length() > MINS.PASSWORD) {
        // If username already exist in the database
        if (!DBHandler::getResult("SELECT * FROM Users WHERE username = '" + loginInfo.username + "'").empty()) {
            // If hash in DB is equal to current password, return true (as passwords match)
            if(BCrypt::validatePassword(loginInfo.password, DBHandler::getResult(
                                                "SELECT password FROM Users WHERE username = '" + loginInfo.username + "'"))) {
                return ErrorTypes::SUCCESS;
            } else return ErrorTypes::PASSWORDS_DO_NOT_MATCH;
        } else return ErrorTypes::USERNAME_NOT_FOUND;
    }
    return ErrorTypes::NOT_ALL_FIELDS_FILLED;
}

/**
 * Check if the provided signup info is valid.
 * @param signupInfo The signup information to check.
 * @return The type of error result (if none, return SUCCESS).
 */
ErrorTypes Login::isValidSignup(const SignupInfo &signupInfo) {
    // Check if username already exists in users table (as it is pk)
    if (!DBHandler::getResult("SELECT * FROM Users WHERE username = '" + signupInfo.username + "'").empty()) {
        return ErrorTypes::USERNAME_ALREADY_EXISTS;
    }
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
        return ErrorTypes::SUCCESS;
    return ErrorTypes::NOT_ALL_FIELDS_FILLED;
}

/**
 * Check if the provided driver-specific signup info is valid.
 * @param signupInfo The signup information to check.
 * @return True if the information is valid, false otherwise.
 */
bool Login::isValidDriverSignup(const DriverSignupInfo &signupInfo) {
    if (signupInfo.NINumber.length() > MINS.NI_NUMBER &&
        signupInfo.drivingLicenceID.length() > MINS.DRIVING_LICENCE_ID &&
        signupInfo.lorryType.length() > MINS.LORRY_TYPE &&
        signupInfo.lorryReg.length() > MINS.LORRY_REG &&
        signupInfo.companyCity.length() > MINS.COMPANY_CITY &&
        signupInfo.companyAddress.length() > MINS.COMPANY_ADDRESS) {
        RegistrationCheck check = RegistrationCheck(signupInfo.lorryReg);
        if (check.getResponse()) return true;
    }
    return false;
}

/**
 * Check if the provided courier-specific signup info is valid.
 * @param signupInfo The signup information to check.
 * @return True if the information is valid, false otherwise.
 */
bool Login::isValidCourierSignup(const CourierSignupInfo &signupInfo) {
    if (signupInfo.companyName.length() > MINS.COMPANY_NAME &&
        signupInfo.companyPhone.length() > MINS.COMPANY_PHONE &&
        signupInfo.companyAddress.length() > MINS.COMPANY_CITY &&
        signupInfo.companyCity.length() > MINS.COMPANY_CITY)
        return true;
    return false;
}

/**
 * Check if the provided forwarder-specific signup info is valid.
 * @param signupInfo The signup information to check.
 * @return True if the information is valid, false otherwise.
 */
bool Login::isValidForwarderSignup(const ForwarderSignupInfo &signupInfo) {
    if (signupInfo.companyName.length() > MINS.COMPANY_NAME &&
        signupInfo.companyPhone.length() > MINS.COMPANY_PHONE &&
        signupInfo.companyAddress.length() > MINS.COMPANY_CITY &&
        signupInfo.companyCity.length() > MINS.COMPANY_CITY)
        return true;
    return false;
}

/**
 * Check if the provided cargo owner-specific signup info is valid.
 * @param signupInfo The signup information to check.
 * @return True if the information is valid, false otherwise.
 */
bool Login::isValidCargoOwnerSignup(const CargoOwnerSignupInfo &signupInfo) {
    if (signupInfo.goodsCategory.length() > MINS.GOODS_CATEGORY) return true;
    return false;
}

/**
 * Store the signup info into the database.
 * @param signupInfo The signup information to store.
 */
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

/**
 * Store the driver signup info into the database.
 * @param username The username of the driver.
 * @param signupInfo The signup information to store.
 */
void Login::storeDriverSignupDetails(const SignupInfo& username, const DriverSignupInfo &signupInfo) {
    std::stringstream query;
    query   << "INSERT INTO Drivers VALUES ('"
            << username.username << "', '"
            << signupInfo.NINumber << "', '"
            << signupInfo.drivingLicenceID << "', '"
            << signupInfo.lorryType << "', '"
            << signupInfo.lorryReg << "', '"
            << signupInfo.companyCity << "', '"
            << signupInfo.companyAddress << "');";
    DBHandler::writeFields(query.str());
}

/**
 * Store the courier signup info into the database.
 * @param username The username of the courier.
 * @param signupInfo The signup information to store.
 */
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

/**
 * Store the forwarder signup info into the database.
 * @param username The username of the forwarder.
 * @param signupInfo The signup information to store.
 */
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

/**
 * Store the cargo owner signup info into the database.
 * @param username The username of the cargo owner.
 * @param signupInfo The signup information to store.
 */
void Login::storeCargoOwnerSignupDetails(const SignupInfo& username, const CargoOwnerSignupInfo &signupInfo) {
    std::stringstream query;
    query   << "INSERT INTO CargoOwners VALUES ('"
            << username.username << "', '"
            << signupInfo.goodsCategory << "');";
    DBHandler::writeFields(query.str());
}

/**
 * Get the type of the user from the provided login info from the database.
 * @param loginInfo The login information to get the type of the user from.
 * @return The type of the user.
 */
EUserTypes Login::getUserType(const LoginInfo& loginInfo) {
    std::string type = DBHandler::getResult("SELECT type FROM Users WHERE username = '" + loginInfo.username + "';");
    UserTypes userTypes;
    if (type == userTypes.Admin) return EUserTypes::ADMIN;
    if (type == userTypes.Driver) return EUserTypes::DRIVER;
    if (type == userTypes.CargoOwner) return EUserTypes::CARGO_OWNER;
    if (type == userTypes.Forwarder) return EUserTypes::FORWARDER;
    if (type == userTypes.Consignee) return EUserTypes::CONSIGNEE;
    if (type == userTypes.Courier) return EUserTypes::COURIER;
    return EUserTypes::NONE;
}
