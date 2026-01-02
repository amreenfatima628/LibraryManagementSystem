#ifndef CUSTOMERLISTDIALOG_H
#define CUSTOMERLISTDIALOG_H

#include <QDialog>

namespace Ui {
class CustomerListDialog;
}

class CustomerListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerListDialog(QWidget *parent = nullptr);
    ~CustomerListDialog();

private:
    Ui::CustomerListDialog *ui;
};

#endif // CUSTOMERLISTDIALOG_H
