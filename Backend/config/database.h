#ifndef DATABASE_H_
#define DATABASE_H_

// Oracle database connection configuration
namespace DatabaseConfig {
    const char* HOSTNAME = "192.168.137.49";
    const char* PORT = "1521";
    const char* SERVICE_NAME = "xe";
    const char* USERNAME = "DocConnect";
    const char* PASSWORD = "root";
    const char* connString = "localhost:1521/xe";
}

#endif // DATABASE_H_
