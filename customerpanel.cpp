#include "customerpanel.h"
#include "ui_customerpanel.h"
#include "customer.h"
#include <QMessageBox>
#include "lms_core.h"
#include <QTableWidgetItem>
#include "issuebookdialog.h"
#include <QInputDialog>
#include "loginwindow.h"

std::vector<Customer> customers;

CustomerPanel::CustomerPanel(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::CustomerPanel)
{
    ui->setupUi(this);
    ui->tableBooks->setColumnCount(5);
    ui->tableBooks->setHorizontalHeaderLabels(
        QStringList() << "ID" << "Title" << "Author" << "Stock" << "Issued"
        );
    ui->tableBooks->hide();
    setWindowTitle("Customer Panel");
}

CustomerPanel::~CustomerPanel()
{
    delete ui;
}

void CustomerPanel::on_btnLogout_clicked()
{
    // Open login window again
    LoginWindow *login = new LoginWindow();
    login->show();

    // Close current admin panel
    this->close();
}


void CustomerPanel::on_btnReturnBook_clicked()
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


void CustomerPanel::on_btnIssueBook_clicked()
{
    IssueBookDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        on_btnViewBooks_clicked();
    }
}


void CustomerPanel::on_btnViewBooks_clicked()
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

void CustomerPanel::on_tableBooks_cellActivated(int row, int column)
{
    Q_UNUSED(row)
    Q_UNUSED(column)
}

