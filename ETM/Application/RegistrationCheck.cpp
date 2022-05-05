#include "RegistrationCheck.h"

#include <utility>

/**
 * Constructor for the RegistrationCheck class.
 * @param _registrationNumber
 */
RegistrationCheck::RegistrationCheck(std::string _registrationNumber) {
    this->registrationNumber = std::move(_registrationNumber);
    sendRequest();
}

/**
 * Send the request to the API with the given registration number,
 * and if the response returns a 200 (valid), set the isValid variable to true.
 */
void RegistrationCheck::sendRequest() {
    CURL* curl = curl_easy_init();
    const std::string jsonInfo = R"({"registrationNumber": ")" + this->registrationNumber + R"("})";

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, ("x-api-key: " + Secrets::getAPIKey()).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, "https://driver-vehicle-licensing.api.gov.uk/vehicle-enquiry/v1/vehicles");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonInfo.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        long responseCode;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        if (responseCode == 200) {
            this->isValid = true;
        }
    }
}

/**
 * Getter for the isValid variable.
 * @return isValid
 */
bool RegistrationCheck::getResponse() const {
    return this->isValid;
}
