#include "adminpanel.h"
#include "ui_adminpanel.h"
#include <QMessageBox>
#include "lms_core.h"
#include <QTableWidgetItem>
#include "issuebookdialog.h"
#include "addbookdialog.h"
#include <QInputDialog>
#include "addcustomerdialog.h"
#include "loginwindow.h"
#include "customerlistdialog.h"

AdminPanel::AdminPanel(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
    ui->tableBooks->setColumnCount(5);
    ui->tableBooks->setHorizontalHeaderLabels(
        QStringList() << "ID" << "Title" << "Author" << "Stock" << "Issued"
        );
    ui->tableBooks->hide();
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::on_btnViewBooks_clicked()
{
    ui->tableBooks->show();   // show only when clicked

    ui->tableBooks->setRowCount(books.size());

    for (int i = 0; i < books.size(); i++) {
        ui->tableBooks->setItem(i, 0,
                                new QTableWidgetItem(QString::fromStdString(books[i].id)));
        ui->tableBooks->setItem(i, 1,
                                new QTableWidgetItem(QString::fromStdString(books[i].title)));
        ui->tableBooks->setItem(i, 2,
                                new QTableWidgetItem(QString::fromStdString(books[i].author)));
        ui->tableBooks->setItem(i, 3,
                                new QTableWidgetItem(QString::number(books[i].stock)));
        ui->tableBooks->setItem(i, 4,
                                new QTableWidgetItem(QString::number(books[i].issued)));
    }
}

void AdminPanel::on_btnIssueBook_clicked()
{
    IssueBookDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        on_btnViewBooks_clicked();
    }
}

void AdminPanel::on_btnAddBook_clicked()
{
    AddBookDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted){
        on_btnViewBooks_clicked();
    }
}

void AdminPanel::on_btnReturnBook_clicked()
{
    bool ok;
    QString id = QInputDialog::getText(
        this,
        "Return Book",
        "Enter Book ID:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || id.isEmpty())
        return;

    // SIMPLE LOGIC (no bool return)
    for (auto &b : books) {
        if (b.id == id.toStdString() && b.issued) {
            b.stock++;
            b.issued--;
            QMessageBox::information(this, "Success", "Book returned");
            on_btnViewBooks_clicked();   // refresh table
            return;
        }
    }

    QMessageBox::warning(this, "Error", "Book not found or not issued");
}

void AdminPanel::on_btnUpdateBook_clicked()
{
    bool ok;
    QString id = QInputDialog::getText(
        this, "Update Book", "Enter Book ID:",
        QLineEdit::Normal, "", &ok);

    if (!ok || id.isEmpty()) return;

    for (auto &b : books) {
        if (b.id == id.toStdString()) {
            QString title = QInputDialog::getText(
                this, "New Title", "Enter new title:",
                QLineEdit::Normal, b.title.c_str(), &ok);

            if (ok && !title.isEmpty())
                b.title = title.toStdString();

            QString author = QInputDialog::getText(
                this, "New Author", "Enter new author:",
                QLineEdit::Normal, b.author.c_str(), &ok);

            if (ok && !author.isEmpty())
                b.author = author.toStdString();

            int stock = QInputDialog::getInt(
                this, "New Stock", "Enter new Stock:",
                b.stock,0,100,1, &ok);

            if (ok)
                b.stock = stock;

            QMessageBox::information(this, "Updated", "Book updated");
            on_btnViewBooks_clicked();
            saveData();
            return;
        }
    }

    QMessageBox::warning(this, "Error", "Book not found");
}

void AdminPanel::on_btnAddCustomer_clicked()
{
    AddCustomerDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted) {
        Customer c;
        c.id = dlg.getId().toStdString();
        c.name = dlg.getName().toStdString();
        c.password = dlg.getPassword().toStdString();

        saveCustomer(c);
    }
}

void AdminPanel::on_btnLogout_clicked()
{
    // Open login window again
    LoginWindow *login = new LoginWindow();
    login->show();

    // Close current admin panel
    this->close();
}

void AdminPanel::on_btnAddCustumer_clicked()
{
    AddCustomerDialog dlg(this);
    dlg.exec();
}

void AdminPanel::on_btnDeleteCustomer_clicked()
{
    bool ok;
    QString id = QInputDialog::getText(
        this,
        "Delete Customer",
        "Enter Customer ID:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (!ok || id.isEmpty())
        return;

    if (deleteCustomerById(id.toStdString())) {
        QMessageBox::information(this, "Success", "Customer deleted successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Customer not found.");
    }
}
void AdminPanel::on_btnViewCustomers_clicked()
{
    CustomerListDialog dlg(this);
    dlg.exec();   // modal dialog
}
