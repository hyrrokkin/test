#ifndef EMPLOYEE_H
#define EMPLOYEE_H

    #include <string>
    #include <iostream>

    using namespace std;

    class Employee {
        int                             id;

        string                          name;
        string                          surname;
        string                          patronymic;

        string                          position;

        int                             age;

        Employee(
                const int               id,
                const string            name,
                const string            surname,
                const string            patronymic,
                const string            position,
                const int               age
                );
    public:
        Employee(){}
        //Employee(const Employee& obj);

        ~Employee(){}

        void                            setId           (int id);
        void                            setName         (string name);
        void                            setSurname      (string surname);
        void                            setPatronymic   (string patronymic);

        void                            setPosition     (string position);

        void                            setAge          (int    age);

        class EmployeeBuilder {
            int                         id;

            string                      name;
            string                      surname;
            string                      patronymic;

            string                      position;

            int                         age;
        public:
            EmployeeBuilder&            setId           (int id);

            EmployeeBuilder&            setName         (string name);
            EmployeeBuilder&            setSurname      (string surname);
            EmployeeBuilder&            setPatronymic   (string patronymic);

            EmployeeBuilder&            setPosition     (string position);

            EmployeeBuilder&            setAge          (int    age);

            Employee*                   build();
        };

        int                             getId           ()                      const;

        string                          getName         ()                      const;
        string                          getSurname      ()                      const;
        string                          getPatronymic   ()                      const;

        string                          getPosition     ()                      const;

        int                             getAge          ()                      const;

       // Employee& operator=(Employee& employee);

        friend ostream& operator<<(ostream &os, const Employee& employee) {
            return os  << "Employee ( name = " << employee.getName() << ", surname = " << employee.getSurname()
                << ", patronic = " << employee.getPatronymic() << ", position = " << employee.getPatronymic() << ", age = " << employee.getAge() << ')' << endl;
        }
    };



#endif
