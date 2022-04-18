#include "RegistrationCheck.h"

#include <utility>

RegistrationCheck::RegistrationCheck(std::string _registrationNumber) {
    this->registrationNumber = std::move(_registrationNumber);
    sendRequest();
}

void RegistrationCheck::sendRequest() {
    std::ostringstream ret;
    curl::curl_ios<std::ostringstream> writer(ret);

    curl::curl_header header;
    curl::curl_easy easy(writer);

    std::string jsonInfo = R"({"registration": ")" + this->registrationNumber + R"("})";
    header.add(jsonInfo);
    header.add("Content-type: application/json");
    header.add("Accept: application/json");
    header.add("x-api-key: " + Secrets::getAPIKey());
    header.add("X-Correlation-Id: " + Secrets::getCorrelationId());

    easy.add<CURLOPT_HTTPHEADER>(header.get());
    easy.add<CURLOPT_URL>("https://driver-vehicle-licensing.api.gov.uk/vehicle-enquiry/v1/vehicles");
    easy.add<CURLOPT_CUSTOMREQUEST>("POST");
    easy.add<CURLOPT_VERBOSE>(0L);

    try {
        easy.perform();
        auto responseCode = easy.get_info<CURLINFO_RESPONSE_CODE>();
        this->isValid = (responseCode.get() == 200);
    } catch (curl::curl_easy_exception &error) {
        std::cerr<<error.what()<<std::endl;
    }
}

bool RegistrationCheck::getResponse() const {
    return this->isValid;
}
