#ifndef RENDEZVOUS_ROUTES_H_
#define RENDEZVOUS_ROUTES_H_

#include "crow.h"
#include "../controllers/RendezVousController.h"

void setupRendezVousRoutes(crow::SimpleApp& app, OracleConnection& conn);

#endif
