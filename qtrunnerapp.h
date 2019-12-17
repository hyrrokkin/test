#ifndef QTRUNNERAPP_H
#define QTRUNNERAPP_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "core/tree/tree.h"
#include "core/employee/employee.h"
#include "core/data_manager/employees_data_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QtRunnerApp; }
QT_END_NAMESPACE

enum EMPLOYEE_PANE_TYPE {
    NEW,
    CHANGE
};

class QtRunnerApp : public QMainWindow
{
    Q_OBJECT

public:
    QtRunnerApp(QWidget *parent = nullptr);
    ~QtRunnerApp();

private slots:
    void on_remove_button_clicked();

    //void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void hide_property_employee_pane();
    void show_employee_pane(TreeElementContainer<Employee> *employeeNode);
    void show_new_employee_pane(TreeElementContainer<Employee> *employeeNode);

    void on_create_employee_button_clicked();

    void on_close_employee_button_clicked();

    void on_add_button_clicked();

    void show_employees_tree(std::vector<TreeElementContainer<Employee>*>* employees);
    void show_employees_tree_node(TreeElementContainer<Employee>* employee, QTreeWidgetItem *treeItem);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    TreeElementContainer<Employee> *currentEmployeeNode;
    QTreeWidgetItem                *currentTreeItem;
    Ui::QtRunnerApp *ui;
    AbstractEmployeesDataManager<Employee, int>* employDataManager;
    EMPLOYEE_PANE_TYPE employeePaneType;
};
#endif // QTRUNNERAPP_H
