#pragma once

#include <drogon/HttpFilter.h>
#include "dto/ApiResponse.h"

namespace sudharshan::sudharshanmart {

/**
 * @brief AuthFilter validating Drogon server-side session for protected endpoints.
 */
class AuthFilter : public drogon::HttpFilter<AuthFilter> {
public:
    void doFilter(const drogon::HttpRequestPtr& req,
                  drogon::FilterCallback&& fcb,
                  drogon::FilterChainCallback&& fccb) override;
};

} // namespace sudharshan::sudharshanmart
