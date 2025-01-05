#ifndef SEARCH_ROUTES_H
#define SEARCH_ROUTES_H

#include "crow.h"
#include "../controllers/SearchController.h"
#include "crow/middlewares/cors.h"

void setupSearchRoutes(crow::App<crow::CORSHandler>& app, OracleConnection& conn);

#endif
