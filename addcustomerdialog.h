#ifndef ADDCUSTOMERDIALOG_H
#define ADDCUSTOMERDIALOG_H

#include <QDialog>

namespace Ui {
class AddCustomerDialog;
}

class AddCustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomerDialog(QWidget *parent = nullptr);
    ~AddCustomerDialog();

    QString getId() const;
    QString getName() const;
    QString getPassword() const;

private slots:
    void on_btnAdd_clicked();
    void on_btnCancel_clicked();

private:
    Ui::AddCustomerDialog *ui;
};

#endif // ADDCUSTOMERDIALOG_H
