#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QMainWindow>

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent = nullptr);
    ~AdminPanel();

private slots:
    void on_btnViewBooks_clicked();
    void on_btnIssueBook_clicked();

    void on_btnReturnBook_clicked();

    void on_btnAddBook_clicked();

    void on_btnUpdateBook_clicked();

    void on_btnAddCustomer_clicked();

    void on_btnLogout_clicked();

    void on_btnAddCustumer_clicked();

    void on_btnDeleteCustomer_clicked();
    void on_btnViewCustomers_clicked();

private:
    Ui::AdminPanel *ui;
};

#endif // ADMINPANEL_H
