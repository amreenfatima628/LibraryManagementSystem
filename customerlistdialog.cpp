#include "customerlistdialog.h"
#include "ui_customerlistdialog.h"

#include "lms_core.h"

#include <QTableWidgetItem>
#include <QHeaderView>

CustomerListDialog::CustomerListDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CustomerListDialog)
{
    ui->setupUi(this);

    loadCustomer();   // load from customers.txt

    ui->tableCustomers->setRowCount(customers.size());
    ui->tableCustomers->setColumnCount(4);

    int row = 0;
    for (const auto &c : customers) {
        ui->tableCustomers->setItem(row, 0,
                                    new QTableWidgetItem(QString::fromStdString(c.id)));
        ui->tableCustomers->setItem(row, 1,
                                    new QTableWidgetItem(QString::fromStdString(c.name)));
        ui->tableCustomers->setItem(row, 2,
                                    new QTableWidgetItem(QString::fromStdString(c.password)));
        ui->tableCustomers->setItem(row, 3,
                                    new QTableWidgetItem(QString::fromStdString(c.createdAt)));
        ui->tableCustomers->setItem(row, 4,
                                    new QTableWidgetItem(QString::fromStdString(c.createdBy)));
        ui->tableCustomers->setColumnCount(5);
        ui->tableCustomers->setHorizontalHeaderLabels(
            {"ID", "Name", "Contact", "Created At", "Created By"});
        row++;
    }

    ui->tableCustomers->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);
}

CustomerListDialog::~CustomerListDialog()
{
    delete ui;
}
