#include "lms_core.h"
#include <fstream>
#include <sstream>
#include <ctime>

/* -------- GLOBALS -------- */

vector<Book> books;
std::string currentAdminName = "";

static const string ADMIN_FILE = "admin.txt";
static const string CUST_FILE  = "customers.txt";
static const string DATA_FILE  = "library_data.csv";

/* ================= ADMIN ================= */

bool adminExists()
{
    ifstream file(ADMIN_FILE);
    return file.good();
}

void saveAdmin(const Customer& admin)
{
    ofstream file(ADMIN_FILE);
    file << admin.id << "," << admin.password;
    file.close();
}

bool loginAdmin(const string& id, const string& password)
{
    ifstream file(ADMIN_FILE);
    if (!file.is_open()) return false;

    string fileId, filePass;
    getline(file, fileId, ',');
    getline(file, filePass);

    return (id == fileId && password == filePass);
}

/* ================= CUSTOMERS ================= */
std::string CurrentDateTime()
{
    time_t now = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buf);
}
bool loginCustomer(const string& id, const string& password)
{
    ifstream file(CUST_FILE);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Customer c;

        getline(ss, c.id, ',');
        getline(ss, c.name, ',');
        getline(ss, c.password);

        if (c.id == id && c.password == password)
            return true;
    }
    return false;
}

/* ================= BOOKS ================= */

/* LOAD CUSTOMERS */
void loadCustomer()
{
    customers.clear();

    std::ifstream file("customers.txt");
    if (!file.is_open())
        return;

    std::string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Customer c;

        getline(ss, c.id, ',');
        getline(ss, c.name, ',');
        getline(ss, c.password,',');
        getline(ss, c.createdAt,',');
        getline(ss, c.createdBy);

        if (!c.id.empty())
            customers.push_back(c);
    }

    file.close();
}

/* SAVE CUSTOMER */
void saveCustomer(Customer& c)
{
    c.createdAt=CurrentDateTime();
    c.createdBy=currentAdminName;

    customers.push_back(c);

    ofstream file("customers.txt", ios::app);
    if (!file.is_open())
        return;

    file << c.id << ","
         << c.name << ","
         << c.password << ","
         << c.createdAt << ","
         << c.createdBy << "\n";

    file.close();
}

/* LOAD ALL DATA */
void loadAllData()
{
    loadCustomer();

    ifstream file("library_data.csv");
    if (!file.is_open()) return;

    string line;
    getline(file, line); // header

    while (getline(file, line)) {
        stringstream ss(line);
        Book b;
        string issuedStr, stockStr;

        getline(ss, b.id, ',');
        getline(ss, b.title, ',');
        getline(ss, b.author, ',');
        getline(ss, stockStr, ',');
        getline(ss, issuedStr, ',');

        b.stock = stoi(stockStr);
        b.issued = stoi(issuedStr);
        books.push_back(b);
    }
}


void saveData()
{
    ofstream file(DATA_FILE);
    file << "ID,Title,Author,Stock,Issued,Borrower,IssueDate,DueDate\n";

    for (auto& b : books) {
        file << b.id << ","
             << b.title << ","
             << b.author << ","
             << b.stock << ","
             << b.issued << ","
             << b.borrower << ","
             << b.issueDate << ","
             << b.dueDate << "\n";
    }
    file.close();
}

IssueStatus issueBook(const string& bookId, const string& borrowerId)
{
    if (!isCustomerExist(borrowerId) && !isAdminExist(borrowerId)){
        return ISSUE_BORROWER_NOT_FOUND;
    }

    {for (auto& b : books) {
            if (b.id == bookId && b.issued){
                return ISSUE_ALREADY_ISSUED;
            }
        if (b.id == bookId && !b.issued) {
            b.issued = true;
            b.borrower = borrowerId;
            b.dueDate = b.issueDate + (7*24*60*60);
            saveData();
            return ISSUE_OK;
        }
        if (b.id == bookId && b.stock > 0 ){
            if (b.issued < b.stock) {
                b.stock--;
                b.issued++;
                saveData();
                return ISSUE_BOOK_DECREASED;
            }
        }
    }
    return ISSUE_BOOK_NOT_FOUND;
    }
}

void returnBook(const string& bookId)
{
    for (auto& b : books) {
        if (b.id == bookId && b.issued) {
            b.stock++;
            b.issued--;
            b.borrower = "";
            b.issueDate = 0;
            b.dueDate = 0;
            saveData();
            return;
        }
    }
}
void addBook(const Book& b)
{
    books.push_back(b);
    saveData();   // optional but recommended
}
bool deleteCustomerById(const std::string& id)
{
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->id == id) {
            customers.erase(it);

            // rewrite file
            std::ofstream file("customers.txt");
            for (const auto& c : customers) {
                file << c.id << "," << c.name << "," << c.password << "\n";
            }
            file.close();

            return true;
        }
    }
    return false;
}
bool isCustomerExist(const std::string& id)
{
    std::ifstream file("customers.txt");
    if (!file.is_open()) return false;

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string cid;
        getline(ss, cid, ',');
        if (cid == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool isAdminExist(const std::string& id)
{
    std::ifstream file("admin.txt");
    if (!file.is_open()) return false;

    std::string storedId;
    file >> storedId;   // assuming admin.txt stores: adminID password
    file.close();

    return (storedId == id);
}
