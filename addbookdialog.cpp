#include "addbookdialog.h"
#include "ui_addbookdialog.h"
#include "lms_core.h"

AddBookDialog::AddBookDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}

void AddBookDialog::on_btnAdd_clicked()
{
    Book b;
    b.id = ui->editId->text().toStdString();
    b.title = ui->editTitle->text().toStdString();
    b.author = ui->editAuthor->text().toStdString();
    b.stock = ui->editStock->text().toInt();
    b.issued = false;

    addBook(b);    // core function
    accept();      // close dialog
}

void AddBookDialog::on_btnCancel_clicked()
{
    reject();
}
