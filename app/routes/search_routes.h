#ifndef SEARCH_ROUTES_H
#define SEARCH_ROUTES_H

#include "crow.h"
#include "../controllers/SearchController.h"

void setupSearchRoutes(crow::SimpleApp& app, OracleConnection& conn);

#endif
