#ifndef ISSUEBOOKDIALOG_H
#define ISSUEBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class IssueBookDialog;
}

class IssueBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IssueBookDialog(QWidget *parent = nullptr);
    ~IssueBookDialog();

private slots:
    void on_btnIssue_clicked();

    void on_btnCancel_clicked();

private:
    Ui::IssueBookDialog *ui;
};

#endif
