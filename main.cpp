#include "qtrunnerapp.h"
#include "core/employee/employee.h"
#include "core/tree/tree.h"
#include "core/data_manager/employees_data_manager.h"
#include "core/data_manager/sqlite3.h"
#include <iostream>

#include <QApplication>

const char* SQL = "CREATE TABLE IF NOT EXISTS foo(a,b,c); INSERT INTO FOO VALUES(1,2,3); INSERT INTO FOO SELECT * FROM FOO;";

int main(int argc, char *argv[])
{
    //TreeElementContainer<Employee>* employDataManager = new EmployeesDataManager("D://1/employees.sqlite3");

    /*Employee employee = Employee::EmployeeBuilder()
            .setId(0)
            .setName("Геннадий")
            .setSurname("Петров")
            .setPatronymic("Вадимович")
            .setPosition("Генеральный директор")
            .setAge(50)
            .build();

    Employee employee2 = Employee::EmployeeBuilder()
            .setId(1)
            .setName("Алексей")
            .setSurname("Иванов")
            .setPatronymic("Никифорович")
            .setPosition("Заместительт генерального директора")
            .setAge(40)
            .build();

    Employee employee1(employee2);

    std::cout << employee1 << std::endl;*/

    //TreeElementContainer<Employee> root = TreeElementContainer<Employee>::createNode(employee);

    //TreeElementContainer<Employee> node = root.addChild(employee2);

    /*std::cout << (node.getValue()) << std::endl;

    AbstractEmployeesDataManager<Employee, int> *b = new EmployeesDataManager("emplpoyees.sqlite3", 0);

*/
    //TreeElementContainer<Employee> root = TreeElementContainer<Employee>::createNode(employee);

    //



    QApplication a(argc, argv);
    QtRunnerApp w;
    w.show();
    return a.exec();

    //a->create(root);
    //a->create(node);

    /*sqlite3 *db = 0; // хэндл объекта соединение к БД
    char *err = 0;

    // открываем соединение
    if( sqlite3_open("D://1//my_cosy_database1.db", &db) )
    fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));
    // выполняем SQL
    else if (sqlite3_exec(db, SQL, 0, 0, &err))
    {
    fprintf(stderr, "Ошибка SQL: %sn", err);
    sqlite3_free(err);
    }
    // закрываем соединение
    sqlite3_close(db);

    //AbstractEmployeesDataManager<Employee, int> *a = new EmployeesDataManager("D://1/db_name.sqlite");*/


}
