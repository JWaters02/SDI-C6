//
// Created by bobby on 13/12/2021.
//

#include "User.h"


User::User(int id, std::string first_name, std::string last_name, int age, std::string email, std::string username,
           std::string password, std::string phone, std::string home_address, std::string home_city,
           std::string created_at, std::string updated_at, std::string deleted_at, UserTypes type) {
    this->id = id;
    this->first_name = first_name;
    this->last_name = last_name;
    this->age = age;
    this->email = email;
    this->username = username;
    this->password = password;
    this->phone = phone;
    this->home_address = home_address;
    this->home_city = home_city;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = deleted_at;
    this->type = type;
}

void User::printUser() {
    std::cout << "ID: " << this->id << std::endl;
    std::cout << "First Name: " << this->first_name << std::endl;
    std::cout << "Last Name: " << this->last_name << std::endl;
    std::cout << "Age: " << this->age << std::endl;
    std::cout << "Email: " << this->email << std::endl;
    std::cout << "Username: " << this->username << std::endl;
    std::cout << "Password: " << this->password << std::endl;
    std::cout << "Phone: " << this->phone << std::endl;
    std::cout << "Home Address: " << this->home_address << std::endl;
    std::cout << "Home City: " << this->home_city << std::endl;
    std::cout << "Created At: " << this->created_at << std::endl;
    std::cout << "Updated At: " << this->updated_at << std::endl;
    std::cout << "Deleted At: " << this->deleted_at << std::endl;
}
