#include <iostream>
#include <vector>
#include <map>
#include "app/models/User.h"
#include "app/models/OracleConnection.h"

using namespace std;

int main() {
    OracleConnection conn;
    conn.connect();

    // Create a User object
    User user1(1, "Doe", "John", "john.doe@example.com", "password123",
                "123 Street, City", "+123456789", "Homme");

    // Create user in the database
    // cout << "Creating user in the database..." << endl;
    // user1.create(conn);
    // cout << "User created successfully!" << endl;

    // Read user from the database
    cout << "Reading user data..." << endl;
    if (user1.read(conn, 1)) {
        cout << "User details:" << endl;
        cout << "ID: " << user1.getId() << endl;
        cout << "Name: " << user1.getNom() << endl;
    } else {
        cout << "User not found!" << endl;
    }

    // Update user details
    // cout << "Updating user details..." << endl;
    // user1.setNom("Smith");
    // user1.update(conn);
    // cout << "User updated successfully!" << endl;

    // Delete user from the database
    // cout << "Deleting user..." << endl;
    // user1.deleteRecord(conn);
    // cout << "User deleted successfully!" << endl;

    return 0;
}
