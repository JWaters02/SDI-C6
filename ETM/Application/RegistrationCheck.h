//
// Created by root on 4/17/22.
//

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
    RegistrationCheck(std::string _registrationNumber);
    bool getResponse();
};


#endif //ETM_REGISTRATIONCHECK_H
