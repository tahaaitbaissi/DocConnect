#ifndef ADMIN_ROUTES_H
#define ADMIN_ROUTES_H

#include "crow.h"
#include "../controllers/AdminController.h"
#include "crow/middlewares/cors.h"

void setupAdminRoutes(crow::App<crow::CORSHandler>& app, OracleConnection& conn);

#endif
