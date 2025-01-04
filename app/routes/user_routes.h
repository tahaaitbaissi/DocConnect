#ifndef USER_ROUTES_H_
#define USER_ROUTES_H_

#include "crow.h"
#include "../controllers/UserController.h"

void setupUserRoutes(crow::SimpleApp& app, OracleConnection& conn);

#endif
