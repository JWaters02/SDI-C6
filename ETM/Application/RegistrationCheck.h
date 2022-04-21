#ifndef ETM_REGISTRATIONCHECK_H
#define ETM_REGISTRATIONCHECK_H

#include "Secrets.h"
#include "curl/curl.h"
#include "curl/easy.h"

#include <iostream>

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
