#ifndef CORS_HANDLER_H
#define CORS_HANDLER_H

#include <crow.h>

class CORSHandler {
public:
    struct context {}; // Empty context

    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);
};

#endif // CORS_HANDLER_H
