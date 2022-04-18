#ifndef ETM_REGISTRATIONCHECK_H
#define ETM_REGISTRATIONCHECK_H

#include "Secrets.h"
#include "json.hpp"
#include "curl_easy.h"
#include "curl_ios.h"
#include "curl_header.h"

class RegistrationCheck {
private:
    void sendRequest();

    std::string registrationNumber;
    bool isValid = false;

public:
    explicit RegistrationCheck(std::string _registrationNumber);
    [[nodiscard]] bool getResponse() const;
};


#endif //ETM_REGISTRATIONCHECK_H
