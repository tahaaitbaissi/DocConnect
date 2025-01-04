#ifndef PATIENT_ROUTES_H_
#define PATIENT_ROUTES_H_

#include "crow.h"
#include "../controllers/PatientController.h"

void setupPatientRoutes(crow::SimpleApp& app, OracleConnection& conn);

#endif
