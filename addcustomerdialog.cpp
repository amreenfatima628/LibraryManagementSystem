#include "addcustomerdialog.h"
#include "customer.h"
#include "lms_core.h"
#include "ui_addcustomerdialog.h"
#include <QMessageBox>
#include <QDateTime>

AddCustomerDialog::AddCustomerDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AddCustomerDialog)
{
    ui->setupUi(this);
}

AddCustomerDialog::~AddCustomerDialog()
{
    delete ui;
}

QString AddCustomerDialog::getId() const
{
    return ui->editId->text();
}

QString AddCustomerDialog::getName() const
{
    return ui->editName->text();
}

QString AddCustomerDialog::getPassword() const
{
    return ui->editPassword->text();
}

void AddCustomerDialog::on_btnAdd_clicked()
{
    Customer c;
    c.id = ui->editId->text().toStdString();
    c.name = ui->editName->text().toStdString();
    c.password = ui->editPassword->text().toStdString();
    c.createdAt = QDateTime::currentDateTime()
                      .toString("yyyy-MM-dd hh:mm:ss")
                      .toStdString();
    c.createdBy = currentAdminName;

    if (c.id.empty() || c.name.empty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields");
        return;
    }

    saveCustomer(c);

    QMessageBox::information(this, "Success", "Customer added successfully");
    close();
}

void AddCustomerDialog::on_btnCancel_clicked()
{
    reject();
}
