#ifndef ORACLECONNECTION_H_
#define ORACLECONNECTION_H_

#include <oci.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class OracleConnection {
private:
    OCIEnv* env;
    OCIError* err;
    OCIServer* srv;
    OCISession* ses;
    OCISvcCtx* svc_ctx;

    void handleError(sword status);

public:
    OracleConnection();
    void connect();
    vector<map <string, string>> executeQuery(const string& query);
    void executeAndPrintQuery(const char *query);
    int getGeneratedId(const string& sequenceName);
    ~OracleConnection();
};

#endif // ORACLECONNECTION_H_
