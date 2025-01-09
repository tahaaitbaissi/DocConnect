#include "crow.h"
#include "crow/middlewares/cors.h"

#include "app/models/OracleConnection.h"
#include "app/routes/user_routes.h"
#include "app/routes/doctor_routes.h"
#include "app/routes/patient_routes.h"
#include "app/routes/rendezvous_routes.h"
#include "app/routes/search_routes.h"
#include "app/routes/admin_routes.h"
#include <iostream>

int main() {
    // crow::SimpleApp app;
    crow::App<crow::CORSHandler> app;

    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors
    .global()// Set up Oracle connection (replace with actual connection setup)
    .headers("Origin", "Content-Type", "Accept")
    .methods("POST"_method, "GET"_method, "DELETE"_method, "PUT"_method)
    .prefix("/cors")
    .origin("127.0.0.1:3000")
    .prefix("/nocors")
    .ignore();

    OracleConnection conn;
    conn.connect();

    setupUserRoutes(app, conn);
    setupDoctorRoutes(app, conn);
    setupPatientRoutes(app, conn);
    setupRendezVousRoutes(app, conn);
    setupSearchRoutes(app, conn);
    setupAdminRoutes(app, conn);

    // Start the server
    //app.port(8080).multithreaded().run();
    app.port(8080).run();
    return 0;
}
