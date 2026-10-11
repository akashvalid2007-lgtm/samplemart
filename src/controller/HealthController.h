#pragma once

#include <drogon/HttpController.h>
#include "controller/BaseController.h"

namespace sudharshan::sudharshanmart {

class HealthController : public drogon::HttpController<HealthController>, public BaseController {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HealthController::CheckHealth, "/api/v1/health", drogon::Get, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::CorsFilter");
    METHOD_LIST_END

    void CheckHealth(const drogon::HttpRequestPtr& req,
                     std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};

} // namespace sudharshan::sudharshanmart
