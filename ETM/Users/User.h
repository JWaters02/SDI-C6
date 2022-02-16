//
// Created by bobby on 13/12/2021.
//

#ifndef SDI_C6_USER_H
#define SDI_C6_USER_H

#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include "UserUtils.h"

class User {
private:
    std::string first_name;
    std::string last_name;
    int age;
    std::string email;
    std::string username;
    std::string password;
    std::string phone;
    std::string home_address;
    std::string home_city;
    std::string created_at;
    std::string updated_at;
    std::string deleted_at;
    std::string type;

public:
    User(std::string first_name, std::string last_name, int age, std::string email, std::string username,
         std::string password, std::string phone, std::string home_address, std::string home_city,
         std::string created_at, std::string updated_at, std::string deleted_at, std::string type);

    std::string getFirstName() const;
    std::string getLastName() const;
    int getAge() const;
    std::string getEmail() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getPhone() const;
    std::string getHomeAddress() const;
    std::string getHomeCity() const;
    std::string getCreatedAt() const;
    std::string getUpdatedAt() const;
    std::string getDeletedAt() const;

    void setFirstName(std::string first_name);
    void setLastName(std::string last_name);
    void setAge(int age);
    void setEmail(std::string email);
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setPhone(std::string phone);
    void setHomeAddress(std::string home_address);
    void setHomeCity(std::string home_city);
    void setCreatedAt(std::string created_at);
    void setUpdatedAt(std::string updated_at);
    void setDeletedAt(std::string deleted_at);

    void printUser();

    void login();
    void logout();
    void registerUser();
    void updateUser();
    void deleteUser();
};


#endif //SDI_C6_USER_H
