#ifndef RENDEZVOUS_ROUTES_H_
#define RENDEZVOUS_ROUTES_H_

#include "crow.h"
#include "../controllers/RendezVousController.h"
#include "crow/middlewares/cors.h"

void setupRendezVousRoutes(crow::App<crow::CORSHandler>& app, OracleConnection& conn);

#endif
