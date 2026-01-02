#include "issuebookdialog.h"
#include "ui_issuebookdialog.h"
#include <QMessageBox>
#include "lms_core.h"

IssueBookDialog::IssueBookDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::IssueBookDialog)
{
    ui->setupUi(this);
}

IssueBookDialog::~IssueBookDialog()
{
    delete ui;
}

void IssueBookDialog::on_btnIssue_clicked()
{
    std::string bookId = ui->editBookId->text().toStdString();
    std::string borrowerId = ui->editBorrowerId->text().toStdString();

    if (bookId.empty() || borrowerId.empty()) {
        QMessageBox::warning(this, "Input Error",
                             "Please enter Book ID and Borrower ID");
        return;
    }

    IssueStatus result = issueBook(bookId, borrowerId);

    switch (result) {
    case ISSUE_OK:
        ISSUE_BOOK_DECREASED:
        QMessageBox::information(this, "Success",
                                 "Book issued successfully for next 7 days");
        accept();
        break;

    case ISSUE_ALREADY_ISSUED:
        QMessageBox::warning(this, "Stock Finished",
                             "This book's Stock is Finished");
        break;

    case ISSUE_BORROWER_NOT_FOUND:
        QMessageBox::warning(this, "Invalid Borrower",
                             "Borrower ID not found.\nPlease add customer first.");
        break;

    case ISSUE_BOOK_NOT_FOUND:
        QMessageBox::warning(this, "Invalid Book",
                             "Book ID not found");
        break;
    case ISSUE_BOOK_DECREASED:
        break;
    }
}


void IssueBookDialog::on_btnCancel_clicked()
{
    reject();
}

