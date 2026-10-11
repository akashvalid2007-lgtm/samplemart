#pragma once

#include <drogon/HttpFilter.h>
#include <string>

namespace sudharshan::sudharshanmart {

/**
 * @brief HTTP Filter generating unique request UUID and logging lifecycle.
 */
class LoggingFilter : public drogon::HttpFilter<LoggingFilter> {
public:
    void doFilter(const drogon::HttpRequestPtr& req,
                  drogon::FilterCallback&& fcb,
                  drogon::FilterChainCallback&& fccb) override;
};

} // namespace sudharshan::sudharshanmart
