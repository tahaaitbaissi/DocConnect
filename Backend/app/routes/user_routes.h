#ifndef USER_ROUTES_H_
#define USER_ROUTES_H_

#include "crow.h"
#include "../controllers/UserController.h"
#include "crow/middlewares/cors.h"

void setupUserRoutes(crow::App<crow::CORSHandler>& app, OracleConnection& conn);

#endif
