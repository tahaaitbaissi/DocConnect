#ifndef PATIENT_ROUTES_H_
#define PATIENT_ROUTES_H_

#include "crow.h"
#include "../controllers/PatientController.h"
#include "crow/middlewares/cors.h"

void setupPatientRoutes(crow::App<crow::CORSHandler>& app, OracleConnection& conn);

#endif
