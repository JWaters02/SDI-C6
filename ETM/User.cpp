//
// Created by bobby on 13/12/2021.
//

#include "User.h"


User::User(int id, std::string first_name, std::string last_name, std::string age, std::string email, std::string username,
           std::string password, std::string phone, std::string home_address, std::string home_city,
           std::string business_address, std::string business_city, std::string country, std::string created_at,
           std::string updated_at, std::string deleted_at) {
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
    this->business_address = business_address;
    this->business_city = business_city;
    this->country = country;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = deleted_at;
}

int getId() {return this->id;}
std::string getFirstName() {return this->first_name;}
std::string getLastName() {return this->last_name;}
std::string getAge() {return this->age;}
std::string getEmail() {return this->email;}
std::string getUsername() {return this->username;}
std::string getPassword() {return this->password;}
std::string getPhone() {return this->phone;}
std::string getHomeAddress() {return this->home_address;}
std::string getHomeCity() {return this->home_city;}
std::string getBusinessAddress() {return this->business_address;}
std::string getBusinessCity() {return this->business_city;}
std::string getCountry() {return this->country;}
std::string getCreatedAt() {return this->created_at;}
std::string getUpdatedAt() {return this->updated_at;}
std::string getDeletedAt() {return this->deleted_at;}

void setId(int id) {this->id = id;}
void setFirstName(std::string first_name) {this->first_name = first_name;}
void setLastName(std::string last_name) {this->last_name = last_name;}
void setAge(std::string age) {this->age = age;}
void setEmail(std::string email) {this->email = email;}
void setUsername(std::string username) {this->username = username;}
void setPassword(std::string password) {this->password = password;}
void setPhone(std::string phone) {this->phone = phone;}
void setHomeAddress(std::string home_address) {this->home_address = home_address;}
void setHomeCity(std::string home_city) {this->home_city = home_city;}
void setBusinessAddress(std::string business_address) {this->business_address = business_address;}
void setBusinessCity(std::string business_city) {this->business_city = business_city;}
void setCountry(std::string country) {this->country = country;}
void setCreatedAt(std::string created_at) {this->created_at = created_at;}
void setUpdatedAt(std::string updated_at) {this->updated_at = updated_at;}
void setDeletedAt(std::string deleted_at) {this->deleted_at = deleted_at;}

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
    std::cout << "Business Address: " << this->business_address << std::endl;
    std::cout << "Business City: " << this->business_city << std::endl;
    std::cout << "Country: " << this->country << std::endl;
    std::cout << "Created At: " << this->created_at << std::endl;
    std::cout << "Updated At: " << this->updated_at << std::endl;
    std::cout << "Deleted At: " << this->deleted_at << std::endl;
}
