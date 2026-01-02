#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include "loginwindow.h"
#include "lms_core.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loadCustomer();
    loadAllData();

    if (!adminExists()) {
        Customer admin;
        admin.id = "admin";
        admin.password = "admin123";
        saveAdmin(admin);
    }

    LoginWindow w;
    w.show();
    return a.exec();
}
