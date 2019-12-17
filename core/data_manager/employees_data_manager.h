#ifndef EMPLOYEESDATAMANAGER_H
#define EMPLOYEESDATAMANAGER_H

#include <QtSql>
#include "../employee/employee.h"
#include "../tree/tree.h"

using namespace std;

template <typename E, typename K>
class AbstractEmployeesDataManager {
    string  db_name;
    QSqlDatabase sdb;

    virtual void                                            check_table_exist()                                                 = 0;
protected:
    QSqlQuery *query;
                                                            AbstractEmployeesDataManager    (string db_name);
public:
    virtual                                                 ~AbstractEmployeesDataManager   ();

    virtual void                                            create          (TreeElementContainer<E>* entity)                   = 0;
    virtual void                                            update          (TreeElementContainer<E>* entity)                   = 0;
    virtual void                                            remove          (TreeElementContainer<E>* entity)                   = 0;

    virtual std::vector<TreeElementContainer<E>*>*          load            ()                                                  = 0;

    virtual void                                            remove_child    (int id)                                            = 0;
            bool                                            open_connection (string db_name);
            void                                            close_connection();
};


class EmployeesDataManager : public virtual AbstractEmployeesDataManager<Employee, int> {
    int last_id = -1;

    void load_subordinates(TreeElementContainer<Employee>* entity);

protected:
    virtual void                                            check_table_exist   ();
    virtual void                                            remove_child        (int id);
public:
    EmployeesDataManager(string db_name);
    ~EmployeesDataManager();

    virtual void                                            create              (TreeElementContainer<Employee>* entity);
    virtual void                                            update              (TreeElementContainer<Employee>* entity);
    virtual void                                            remove              (TreeElementContainer<Employee>* entity);

    virtual std::vector<TreeElementContainer<Employee>*>*   load                ();
};

#endif
