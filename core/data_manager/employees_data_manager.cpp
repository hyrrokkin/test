#include "employees_data_manager.h"

const char* SQL_QUERY_TABLE_EMPLOYEES_EXIST = "CREATE TABLE IF NOT EXISTS EMPLOYEE ("
                                        "id         INTEGER PRIMARY KEY,"
                                        "name       TEXT    NOT NULL,"
                                        "surname    TEXT    NOT NULL,"
                                        "patronymic TEXT            ,"
                                        "position   TEXT    NOT NULL,"
                                        "age        INTEGER NOT NULL"
                                    ");";

const char* SQL_QUERY_TABLE_SUPERVISOR_EXIST = "CREATE TABLE IF NOT EXISTS SUPERVISOR("
                                               "supervisor_id                   INTEGER NOT NULL,"
                                               "subordinate_id                  INTEGER NOT NULL,"
                                               "FOREIGN KEY (supervisor_id)     REFERENCES EMPLOYEE(id)"
                                               "FOREIGN KEY (subordinate_id)    REFERENCES EMPLOYEE(id)"
                                               "ON DELETE CASCADE"
                                               ");";

const char* EMPLOYEES_INSERT_TEMPLATE       = "INSERT INTO EMPLOYEE (id, name, surname, patronymic, position, age) VALUES (:id, :name, :surname, :patronymic, :position, :age);";
const char* SUPERVISION_INSERT_TEMPLATE     = "INSERT INTO SUPERVISOR (supervisor_id, subordinate_id) VALUES (:supervisor_id, :subordinate_id);";

const char* LOAD_EMPLOYEES_TEMPLATE         = "SELECT * FROM EMPLOYEE ORDER BY ID";

const char* ROOTS_EMPLOYEES_TEMPLATE        = "SELECT * FROM EMPLOYEE WHERE id NOT IN (SELECT subordinate_id FROM SUPERVISOR)";
const char* LOAD_SUPERVISION_TEMPLATE       = "SELECT * from EMPLOYEE WHERE id IN (SELECT subordinate_id FROM SUPERVISOR WHERE supervisor_id == :id)";

const char* UPDATE_EMPLOYEE_TEMPLATE        = "UPDATE EMPLOYEE SET name = :name, surname = :surname, patronymic = :patronymic, position = :position, age = :age WHERE id = :id";

const char* REMOVE_TEMPLATE                 = "DELETE FROM EMPLOYEE WHERE id == :id";
const char* REMOVE_SUPERVISION_TEMPLATE_1   = "DELETE FROM SUPERVISOR WHERE supervisor_id == :id";
const char* REMOVE_SUPERVISION_TEMPLATE_2   = "DELETE FROM SUPERVISOR WHERE subordinate_id == :id";


template <typename E, typename K>
AbstractEmployeesDataManager<E, K>::AbstractEmployeesDataManager(string db_name) {
    open_connection(db_name);

    query = new QSqlQuery();
}

template <typename E, typename K>
AbstractEmployeesDataManager<E, K>::~AbstractEmployeesDataManager() {
    close_connection();
}

template <typename E, typename K>
void AbstractEmployeesDataManager<E, K>::close_connection() {
    sdb.close();
}

template <typename E, typename K>
bool AbstractEmployeesDataManager<E, K>::open_connection(string db_name) {
    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(db_name.c_str());

    if (!sdb.open()) {
        qDebug() << sdb.lastError().text();

        throw exception();
    }
}

EmployeesDataManager::EmployeesDataManager(string db_name) : AbstractEmployeesDataManager<Employee, int>(db_name) {
    check_table_exist();
}

EmployeesDataManager::~EmployeesDataManager() {
    close_connection();
    delete &query;
}

void EmployeesDataManager::check_table_exist() {
    query->exec(SQL_QUERY_TABLE_EMPLOYEES_EXIST);
    query->exec(SQL_QUERY_TABLE_SUPERVISOR_EXIST);
}

void EmployeesDataManager::create(TreeElementContainer<Employee>* entity) {
    last_id++;

    entity->getValue()->setId(last_id);

    query->prepare(EMPLOYEES_INSERT_TEMPLATE);

    query->bindValue(":id"          , entity->getValue()->getId());
    query->bindValue(":name"        , entity->getValue()->getName()       .c_str());
    query->bindValue(":surname"     , entity->getValue()->getSurname()    .c_str());
    query->bindValue(":patronymic"  , entity->getValue()->getPatronymic() .c_str());
    query->bindValue(":position"    , entity->getValue()->getPosition()   .c_str());
    query->bindValue(":age"         , entity->getValue()->getAge());

    query->exec();

    if (entity->getParent() != NULL) {
        query->prepare(SUPERVISION_INSERT_TEMPLATE);

        query->bindValue(":supervisor_id"   , entity->getParent()->getValue()->getId());

        query->bindValue(":subordinate_id"  , entity->getValue()->getId());

        query->exec();
    }
}

void EmployeesDataManager::update(TreeElementContainer<Employee>* entity) {
    query->prepare(UPDATE_EMPLOYEE_TEMPLATE);

    query->bindValue(":name"        , entity->getValue()->getName()       .c_str());
    query->bindValue(":surname"     , entity->getValue()->getSurname()    .c_str());
    query->bindValue(":patronymic"  , entity->getValue()->getPatronymic() .c_str());
    query->bindValue(":position"    , entity->getValue()->getPosition()   .c_str());
    query->bindValue(":age"         , entity->getValue()->getAge());
    query->bindValue(":id"          , entity->getValue()->getId());

    query->exec();
}

void EmployeesDataManager::remove(TreeElementContainer<Employee>* entity) {
    remove_child(entity->getValue()->getId());

    query->prepare(REMOVE_TEMPLATE);
    query->bindValue(":id"          , entity->getValue()->getId());
    query->exec();

    query->prepare(REMOVE_SUPERVISION_TEMPLATE_1);
    query->bindValue(":id"          , entity->getValue()->getId());
    query->exec();

    query->prepare(REMOVE_SUPERVISION_TEMPLATE_2);
    query->bindValue(":id"          , entity->getValue()->getId());
    query->exec();
}

void EmployeesDataManager::remove_child(int id) {
    QSqlQuery *query = new QSqlQuery();

    query->prepare(LOAD_SUPERVISION_TEMPLATE);
    query->bindValue(":id"          , id);
    query->exec();

    while (query-> next()) {
        int id = query->value(0).toInt();

        last_id = last_id == id ? last_id - 1 : last_id;

        remove_child(id);

        QSqlQuery *query = new QSqlQuery();

        query->prepare(REMOVE_TEMPLATE);
        query->bindValue(":id"          , id);
        query->exec();

        query->prepare(REMOVE_SUPERVISION_TEMPLATE_1);
        query->bindValue(":id"          , id);
        query->exec();

        query->prepare(REMOVE_SUPERVISION_TEMPLATE_2);
        query->bindValue(":id"          , id);
        query->exec();

        delete query;
    }

    delete query;
}

void EmployeesDataManager::load_subordinates(TreeElementContainer<Employee>* entity) {
    QSqlQuery *query = new QSqlQuery();

    query->prepare(LOAD_SUPERVISION_TEMPLATE);
    query->bindValue(":id"          , entity->getValue()->getId());
    query->exec();

    while (query-> next()) {
        last_id = last_id < query->value(0).toInt() ? query->value(0).toInt() : last_id;

        Employee* employee = Employee::EmployeeBuilder()
                .setId(query->value(0).toInt())
                .setName(query->value(1).toString().toStdString())
                .setSurname(query->value(2).toString().toStdString())
                .setPatronymic(query->value(3).toString().toStdString())
                .setPosition(query->value(4).toString().toStdString())
                .setAge(query->value(5).toInt())
                .build();


        TreeElementContainer<Employee>* node = entity->addChild(employee);

        load_subordinates(node);
    }
}

std::vector<TreeElementContainer<Employee>*>* EmployeesDataManager::load() {
    std::vector<TreeElementContainer<Employee>*>* employees = new vector<TreeElementContainer<Employee>*>();

    query->prepare(ROOTS_EMPLOYEES_TEMPLATE);
    query->exec();

    while (query -> next()) {
        last_id = last_id < query->value(0).toInt() ? query->value(0).toInt() : last_id;

        Employee* employee = Employee::EmployeeBuilder()
                .setId(query->value(0).toInt())
                .setName(query->value(1).toString().toStdString())
                .setSurname(query->value(2).toString().toStdString())
                .setPatronymic(query->value(3).toString().toStdString())
                .setPosition(query->value(4).toString().toStdString())
                .setAge(query->value(5).toInt())
                .build();

        TreeElementContainer<Employee>* root = TreeElementContainer<Employee>::createNode(employee);

        employees->push_back(root);

        load_subordinates(root);
    }

    return employees;
}
