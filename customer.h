#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

struct Customer {
    std::string id;
    std::string name;
    std::string password;
    std::string createdAt;
    std::string createdBy;
};

#endif // CUSTOMER_H
