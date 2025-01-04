#ifndef DOCTOR_ROUTES_H_
#define DOCTOR_ROUTES_H_

#include "crow.h"
#include "../controllers/DoctorController.h"


void setupDoctorRoutes(crow::SimpleApp& app, OracleConnection& conn);

#endif
