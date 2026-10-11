#include "filter/LoggingFilter.h"
#include <drogon/utils/Utilities.h>
#include <spdlog/spdlog.h>

namespace sudharshan::sudharshanmart {

void LoggingFilter::doFilter(const drogon::HttpRequestPtr& req,
                             drogon::FilterCallback&& /*fcb*/,
                             drogon::FilterChainCallback&& fccb) {
    // Generate or propagate request ID
    std::string request_id = req->getHeader("X-Request-Id");
    if (request_id.empty()) {
        request_id = drogon::utils::getUuid();
    }
    req->setParameter("request_id", request_id);

    spdlog::info("[{}] {} {} from {}",
                 request_id,
                 req->getMethodString(),
                 req->getPath(),
                 req->getPeerAddr().toIpPort());

    fccb();
}

} // namespace sudharshan::sudharshanmart
