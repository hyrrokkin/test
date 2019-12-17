#include "qtrunnerapp.h"
#include "core/employee/employee.h"
#include "core/tree/tree.h"
#include "core/data_manager/employees_data_manager.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QtRunnerApp w;
    w.show();
    return a.exec();
}
