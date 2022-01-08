//
// Created by bobby on 13/12/2021.
//

#ifndef SDI_C6_USER_H
#define SDI_C6_USER_H

#include <string>
#include <vector>
#include <iostream>
#include <time.h>

class User {
private:
    int id;
    std::string first_name;
    std::string last_name;
    std::string age;
    std::string email;
    std::string username;
    std::string password;
    std::string phone;
    std::string home_address;
    std::string home_city;
    std::string business_address;
    std::string business_city;
    std::string country;
    std::string created_at;
    std::string updated_at;
    std::string deleted_at;

public:
    User(int id, std::string first_name, std::string last_name, std::string age, std::string email, std::string username,
         std::string password, std::string phone, std::string home_address, std::string home_city,
         std::string business_address, std::string business_city, std::string country, std::string created_at,
         std::string updated_at, std::string deleted_at);

    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getAge() const;
    std::string getEmail() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getPhone() const;
    std::string getHomeAddress() const;
    std::string getHomeCity() const;
    std::string getBusinessAddress() const;
    std::string getBusinessCity() const;
    std::string getCountry() const;
    std::string getCreatedAt() const;
    std::string getUpdatedAt() const;
    std::string getDeletedAt() const;

    void setId(int id);
    void setFirstName(std::string first_name);
    void setLastName(std::string last_name);
    void setAge(std::string age);
    void setEmail(std::string email);
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setPhone(std::string phone);
    void setHomeAddress(std::string home_address);
    void setHomeCity(std::string home_city);
    void setBusinessAddress(std::string business_address);
    void setBusinessCity(std::string business_city);
    void setCountry(std::string country);
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
