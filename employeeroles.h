#ifndef EMPLOYEEROLES_H
#define EMPLOYEEROLES_H
#include <QString>

class EmployeeRoles {
public:
    enum Role {
        Employee = 1,
        Admin = 2,
        SysAdmin = 3
    };

    static QString toString(Role r) {
        switch (r) {
        case Employee: return "Employee";
        case Admin: return "Admin";
        case SysAdmin: return "SysAdmin";
        }
        return "Unknown";
    }
};

#endif // EMPLOYEEROLES_H
