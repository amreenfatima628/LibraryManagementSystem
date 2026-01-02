#ifndef LMS_CORE_H
#define LMS_CORE_H

#include <vector>
#include <string>
#include <ctime>
#include "customer.h"

using namespace std;

/* -------- STRUCTS -------- */

struct Book {
    string id;
    string title;
    string author;
    int stock = 0;
    int issued;
    string borrower;
    time_t issueDate = 0;
    time_t dueDate = 0;
};

/* -------- GLOBAL DATA -------- */

extern std::vector<Book> books;
extern std::vector<Customer> customers;
extern std::string currentAdminName;

/* -------- LOGIN -------- */

bool loginAdmin(const std::string& id, const std::string& password);
bool loginCustomer(const std::string& id, const std::string& password);

/* -------- ADMIN -------- */
struct Admin{
    std::string id;
    std::string password;
};
extern Admin adminAccount;

bool adminExists();
void saveAdmin(const Customer& admin);
bool validateAdminLogin(const std::string& id, const std::string& password);

/* -------- CUSTOMER -------- */

void loadAllData();
void loadCustomer();
void saveCustomer(Customer &c);
bool deleteCustomerById(const std::string& id);

/* -------- BOOKS -------- */

void saveData();
void addBook(const Book& b);
void updateBook(const string& id, const string& title, const string& author);
void returnBook(const string& id);
bool isCustomerExist(const std::string& id);
bool isAdminExist(const std::string& id);
enum IssueStatus{
    ISSUE_OK,
    ISSUE_BOOK_NOT_FOUND,
    ISSUE_ALREADY_ISSUED,
    ISSUE_BORROWER_NOT_FOUND,
    ISSUE_BOOK_DECREASED
};
IssueStatus issueBook(const std::string& bookId, const std::string& borrowerId);

#endif
