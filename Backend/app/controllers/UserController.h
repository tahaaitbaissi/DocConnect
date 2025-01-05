#ifndef USERCONTROLLER_H_
#define USERCONTROLLER_H_

#include <vector>
#include <string>
#include "../models/User.h"
#include "../models/OracleConnection.h"

using namespace std;

class UserController {
public:
    UserController();
    ~UserController();

    void addUser(OracleConnection& conn, User& user);
    bool getUser(OracleConnection& conn, int id, User& user);
    vector<User> getAllUsers(OracleConnection& conn);
    bool updateUser(OracleConnection& conn, User& user);
    bool deleteUser(OracleConnection& conn, int id);

    // Authentication
    User login(OracleConnection& conn, string email, string password);
    bool registerUser(OracleConnection& conn, User* user);
};

#endif // USERCONTROLLER_H_
