#include "employee.h"

Employee::Employee (
        const int       id,
        const string    name,
        const string    surname,
        const string    patronymic,
        const string    position,
        const int       age
        ) {
    this->id            = id;
    this->name          = name;
    this->surname       = surname;
    this->patronymic    = patronymic;
    this->position      = position;
    this->age           = age;
}

void Employee::setId (int id) {
    this->id = id;
}

void Employee::setName (string name) {
    this->name = name;
}

void Employee::setSurname (string surname) {
    this->surname = surname;
}

void Employee::setPatronymic (string patronymic) {
    this->patronymic = patronymic;
}

void Employee::setPosition (string position) {
    this->position = position;
}

void Employee::setAge (int age) {
    this->age = age;
}

int Employee::getId() const {
    return this->id;
}

string Employee::getName() const {
    return this->name;
}

string Employee::getSurname() const {
    return this->surname;
}

string Employee::getPatronymic() const {
    return this->patronymic;
}

string Employee::getPosition() const {
    return this->position;
}

int Employee::getAge() const {
    return this->age;
}

Employee::EmployeeBuilder& Employee::EmployeeBuilder::setId(int id) {
    this->id = id;

    return *this;
}

Employee::EmployeeBuilder& Employee::EmployeeBuilder::setName(string name) {
    this->name = name;

    return *this;
}

Employee::EmployeeBuilder& Employee::EmployeeBuilder::setSurname(string surname) {
    this->surname = surname;

    return *this;
}

Employee::EmployeeBuilder& Employee::EmployeeBuilder::setPatronymic(string patronymic) {
    this->patronymic = patronymic;

    return *this;
}

Employee::EmployeeBuilder& Employee::EmployeeBuilder::setPosition(string position) {
    this->position = position;

    return *this;
}

Employee::EmployeeBuilder& Employee::EmployeeBuilder::setAge(int age) {
    this->age = age;

    return *this;
}

Employee* Employee::EmployeeBuilder::build() {
    return new Employee(this->id, this->name, this->surname, this->patronymic, this->position, this->age);
}
