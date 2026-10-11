#include "filter/AuthFilter.h"
#include <spdlog/spdlog.h>

namespace sudharshan::sudharshanmart {

void AuthFilter::doFilter(const drogon::HttpRequestPtr& req,
                          drogon::FilterCallback&& fcb,
                          drogon::FilterChainCallback&& fccb) {
    auto session = req->session();
    if (!session || !session->find("user_id")) {
        // Also support Bearer mock token header for programmatic / testing clients
        std::string auth_header = req->getHeader("Authorization");
        if (auth_header.find("Bearer user_") == 0) {
            std::string id_str = auth_header.substr(12);
            try {
                int64_t user_id = std::stoll(id_str);
                req->setParameter("session_user_id", std::to_string(user_id));
                fccb();
                return;
            } catch (...) {}
        }

        spdlog::warn("Unauthorized access blocked at {}", req->getPath());
        auto err_json = ApiResponse<>::Error("UNAUTHORIZED", "Active session or authorization token required");
        auto resp = ApiResponse<>::ToHttpResponse(err_json, drogon::k401Unauthorized);
        fcb(resp);
        return;
    }

    fccb();
}

} // namespace sudharshan::sudharshanmart
