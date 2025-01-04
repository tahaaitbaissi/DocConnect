#ifndef ADMIN_ROUTES_H
#define ADMIN_ROUTES_H

#include "crow.h"
#include "../controllers/AdminController.h"

void setupAdminRoutes(crow::SimpleApp& app, OracleConnection& conn);

#endif
