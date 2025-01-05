#include "corshandler.h"

// Optional: Add necessary headers for handling CORS

void CORSHandler::before_handle(crow::request&, crow::response& res, context& ) {
    // Add CORS headers before handling the request
    // res.add_header("Access-Control-Allow-Origin", "http://localhost:3000/");
    // res.add_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    // res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");

    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Headers", "*");
    res.add_header("Access-Control-Allow-Methods", "*");
}

void CORSHandler::after_handle(crow::request&, crow::response&, context&) {
    // Intentionally left empty
}
