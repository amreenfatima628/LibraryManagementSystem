#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include "adminpanel.h"
#include "customerpanel.h"
#include "lms_core.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    loadCustomer();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnLogin_clicked()
{
    QString id   = ui->editId->text();
    QString pass = ui->editPassword->text();

    if (loginAdmin(id.toStdString(), pass.toStdString())) {
        currentAdminName = id.toStdString();
        AdminPanel *a = new AdminPanel();
        a->show();
        close();
    }
    else if (loginCustomer(id.toStdString(), pass.toStdString())) {
        CustomerPanel *c = new CustomerPanel();
        c->show();
        close();
    }
    else {
        QMessageBox::warning(this, "Error", "Invalid login");
    }
}

void LoginWindow::on_btnExit_clicked()
{
    close();
}

