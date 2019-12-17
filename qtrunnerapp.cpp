#include "qtrunnerapp.h"
#include "ui_qtrunnerapp.h"

//Q_DECLARE_METATYPE(TreeElementContainer<Employee>);

#define FIXED_LINE_WIDTH            300

typedef TreeElementContainer<Employee> *employeeContainer;
Q_DECLARE_METATYPE(employeeContainer)

void setFontLabel(QLabel *label) {
    QFont font = label->font();

    font.setPointSize(15);
    font.setBold(true);
    font.setFamily("monospace");

    label->setFont(font);
}


QtRunnerApp::QtRunnerApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtRunnerApp)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,2);

    setFontLabel(ui->surnameLabel);
    setFontLabel(ui->nameLabel);
    setFontLabel(ui->patronymicLabel);
    setFontLabel(ui->positionLabel);
    setFontLabel(ui->ageLabel);

    ui->ageLineEdit->setValidator(new QIntValidator(0, 100, this));

    ui->treeWidget->setHeaderHidden(true);
    ui->gridLayout_2->setAlignment(Qt::AlignTop);

    ui->surnameLineEditor       ->setFixedWidth(FIXED_LINE_WIDTH);
    ui->nameLaneEditor          ->setFixedWidth(FIXED_LINE_WIDTH);
    ui->patronymicLineEdit      ->setFixedWidth(FIXED_LINE_WIDTH);
    ui->positionLineEditor_2    ->setFixedWidth(FIXED_LINE_WIDTH);
    ui->ageLineEdit             ->setFixedWidth(FIXED_LINE_WIDTH);

    hide_property_employee_pane();

    employDataManager = new EmployeesDataManager("D://1/employees.sqlite3");

    show_employees_tree(employDataManager->load());
}

void QtRunnerApp::show_employees_tree_node(TreeElementContainer<Employee>* employeeParent, QTreeWidgetItem *treeItem) {
    for (TreeElementContainer<Employee>* employee : *(employeeParent->getChildren())) {
        std::string text = employee->getValue()->getSurname() + " " + employee->getValue()->getName() + " " + employee->getValue()->getPatronymic() + ": " + employee->getValue()->getPosition();

        QTreeWidgetItem *currentTreeItem = new QTreeWidgetItem(treeItem);
        currentTreeItem->setText(0, text.c_str());
        currentTreeItem->setData(0, Qt::UserRole, QVariant::fromValue(employee));

        show_employees_tree_node(employee, currentTreeItem);
    }
}

void QtRunnerApp::show_employees_tree(std::vector<TreeElementContainer<Employee>*>* employees) {
    for (TreeElementContainer<Employee>* employee : *employees) {
        std::string text = employee->getValue()->getSurname() + " " + employee->getValue()->getName() + " " + employee->getValue()->getPatronymic() + ": " + employee->getValue()->getPosition();

        QTreeWidgetItem *currentTreeItem = new QTreeWidgetItem(ui->treeWidget);
        currentTreeItem->setText(0, text.c_str());
        currentTreeItem->setData(0, Qt::UserRole, QVariant::fromValue(employee));

        show_employees_tree_node(employee, currentTreeItem);
    }
}

QtRunnerApp::~QtRunnerApp() {
    delete ui;
}

void QtRunnerApp::hide_property_employee_pane() {
    ui->surnameLabel->setVisible(false);
    ui->nameLabel->setVisible(false);
    ui->patronymicLabel->setVisible(false);
    ui->positionLabel->setVisible(false);
    ui->ageLabel->setVisible(false);

    ui->surnameLineEditor->setText("");
    ui->nameLaneEditor->setText("");
    ui->patronymicLineEdit->setText("");
    ui->positionLineEditor_2->setText("");
    ui->ageLineEdit->setText("");

    ui->surnameLineEditor->setVisible(false);
    ui->nameLaneEditor->setVisible(false);
    ui->patronymicLineEdit->setVisible(false);
    ui->positionLineEditor_2->setVisible(false);
    ui->ageLineEdit->setVisible(false);

    ui->create_employee_button->setVisible(false);
    ui->close_employee_button->setVisible(false);
}

void QtRunnerApp::show_new_employee_pane(TreeElementContainer<Employee> *employeeNode) {
    employeePaneType = NEW;

    ui->surnameLabel->setVisible(true);
    ui->nameLabel->setVisible(true);
    ui->patronymicLabel->setVisible(true);
    ui->positionLabel->setVisible(true);
    ui->ageLabel->setVisible(true);

    if (employeeNode == NULL) {
        currentEmployeeNode = NULL;
        currentTreeItem = NULL;


    } else {
        currentEmployeeNode = employeeNode;
        currentTreeItem = ui->treeWidget->selectedItems()[0];
    }

    ui->surnameLineEditor->setText("");
    ui->nameLaneEditor->setText("");
    ui->patronymicLineEdit->setText("");
    ui->positionLineEditor_2->setText("");
    ui->ageLineEdit->setText("");

    ui->surnameLineEditor->setVisible(true);
    ui->nameLaneEditor->setVisible(true);
    ui->patronymicLineEdit->setVisible(true);
    ui->positionLineEditor_2->setVisible(true);
    ui->ageLineEdit->setVisible(true);

    ui->create_employee_button->setVisible(true);
    ui->close_employee_button->setVisible(true);
}

void QtRunnerApp::show_employee_pane(TreeElementContainer<Employee> *employeeNode) {
    employeePaneType = CHANGE;

    ui->surnameLabel->setVisible(true);
    ui->nameLabel->setVisible(true);
    ui->patronymicLabel->setVisible(true);
    ui->positionLabel->setVisible(true);
    ui->ageLabel->setVisible(true);


    ui->surnameLineEditor->setText(employeeNode->getValue()->getSurname().c_str());
    ui->nameLaneEditor->setText(employeeNode->getValue()->getName().c_str());
    ui->patronymicLineEdit->setText(employeeNode->getValue()->getPatronymic().c_str());
    ui->positionLineEditor_2->setText(employeeNode->getValue()->getPosition().c_str());
    ui->ageLineEdit->setText(std::to_string(employeeNode->getValue()->getAge()).c_str());

    ui->surnameLineEditor->setVisible(true);
    ui->nameLaneEditor->setVisible(true);
    ui->patronymicLineEdit->setVisible(true);
    ui->positionLineEditor_2->setVisible(true);
    ui->ageLineEdit->setVisible(true);

    ui->create_employee_button->setVisible(true);
    ui->close_employee_button->setVisible(true);
}

void QtRunnerApp::on_add_button_clicked() {
    if (ui->treeWidget->selectedItems().size() == 0) {
        show_new_employee_pane(NULL);

        qDebug("show empty employ pane");
    } else {
        QVariant var = ui->treeWidget->selectedItems()[0]->data(0, Qt::UserRole);

        TreeElementContainer<Employee> *employeeNode = static_cast<employeeContainer>(var.value<employeeContainer>());

        show_new_employee_pane(employeeNode);

        qDebug("show custom employ pane");
    }
}

void QtRunnerApp::on_create_employee_button_clicked() {
    if (employeePaneType == NEW) {
        Employee* employee = Employee::EmployeeBuilder()
                .setName(ui->nameLaneEditor->text().toStdString())
                .setSurname(ui->surnameLineEditor->text().toStdString())
                .setPatronymic(ui->patronymicLineEdit->text().toStdString())
                .setPosition(ui->positionLineEditor_2->text().toStdString())
                .setAge(ui->ageLineEdit->text().toInt())
                .build();

        TreeElementContainer<Employee> *employeeNode;

        if (currentEmployeeNode == NULL) {
            employeeNode = TreeElementContainer<Employee>::createNode(employee);
        } else {
            employeeNode = currentEmployeeNode->addChild(employee);
        }

        std::string text = employee->getSurname() + " " + employee->getName() + " " + employee->getPatronymic() + ": " + employee->getPosition();

        if (currentTreeItem == NULL) {
            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
            treeItem->setText(0, text.c_str());
            treeItem->setData(0, Qt::UserRole, QVariant::fromValue(employeeNode));
        } else {
            QTreeWidgetItem *treeItem = new QTreeWidgetItem(currentTreeItem);
            treeItem->setText(0, text.c_str());
            treeItem->setData(0, Qt::UserRole, QVariant::fromValue(employeeNode));
        }

        employDataManager->create(employeeNode);
    }

    if (employeePaneType == CHANGE) {
        currentEmployeeNode->getValue()->setSurname(ui->surnameLineEditor->text().toStdString());
        currentEmployeeNode->getValue()->setName(ui->nameLaneEditor->text().toStdString());
        currentEmployeeNode->getValue()->setPatronymic(ui->patronymicLineEdit->text().toStdString());
        currentEmployeeNode->getValue()->setPosition(ui->positionLineEditor_2->text().toStdString());
        currentEmployeeNode->getValue()->setAge(ui->ageLineEdit->text().toInt());

        std::string text = currentEmployeeNode->getValue()->getSurname() + " " + currentEmployeeNode->getValue()->getName() + " " + currentEmployeeNode->getValue()->getPatronymic() + ": " + currentEmployeeNode->getValue()->getPosition();

        currentTreeItem->setText(0, text.c_str());

        employDataManager->update(currentEmployeeNode);
    }

    hide_property_employee_pane();
    ui->treeWidget->clearSelection();
}

void QtRunnerApp::on_remove_button_clicked()
{
    QVariant var = ui->treeWidget->selectedItems()[0]->data(0, Qt::UserRole);
    TreeElementContainer<Employee> *employeeNode = static_cast<employeeContainer>(var.value<employeeContainer>());

    employDataManager->remove(employeeNode);

    delete ui->treeWidget->selectedItems()[0];

    hide_property_employee_pane();
}

/*void QtRunnerApp::on_treeWidget_customContextMenuRequested(const QPoint &pos) {
    QMenu *menu = new QMenu(this);

    menu->addAction(QString("Новый сотрудник"), this, SLOT(hide_property_employee_pane));

    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
    menu->exec(ui->treeWidget->viewport()->mapToGlobal(pos));
}*/

void QtRunnerApp::on_close_employee_button_clicked() {
    hide_property_employee_pane();
}

void QtRunnerApp::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column) {
    QVariant var = ui->treeWidget->selectedItems()[0]->data(0, Qt::UserRole);
    TreeElementContainer<Employee> *employeeNode = static_cast<employeeContainer>(var.value<employeeContainer>());

    currentEmployeeNode = employeeNode;
    currentTreeItem     = item;

    show_employee_pane(employeeNode);
}
