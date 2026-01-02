#ifndef CUSTOMERPANEL_H
#define CUSTOMERPANEL_H

#include <QMainWindow>

namespace Ui {
class CustomerPanel;
}

class CustomerPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerPanel(QWidget *parent = nullptr);
    ~CustomerPanel();

private slots:
    void on_btnLogout_clicked();

    void on_btnReturnBook_clicked();

    void on_btnIssueBook_clicked();

    void on_btnViewBooks_clicked();

    void on_tableBooks_cellActivated(int row, int column);

private:
    Ui::CustomerPanel *ui;
};

#endif // CUSTOMERPANEL_H
