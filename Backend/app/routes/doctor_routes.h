#ifndef DOCTOR_ROUTES_H_
#define DOCTOR_ROUTES_H_

#include "crow.h"
#include "../controllers/DoctorController.h"
#include "crow/middlewares/cors.h"

void setupDoctorRoutes(crow::App<crow::CORSHandler>& app, OracleConnection& conn);

#endif
