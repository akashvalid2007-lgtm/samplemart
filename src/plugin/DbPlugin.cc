#include "plugin/DbPlugin.h"
#include <spdlog/spdlog.h>

namespace sudharshan::sudharshanmart {

void DbPlugin::initAndStart(const Json::Value& config) {
    std::string db_path = "sudharshanmart.db";
    if (config.isMember("db_path") && config["db_path"].isString()) {
        db_path = config["db_path"].asString();
    }
    spdlog::info("DbPlugin initializing database at: {}", db_path);
    DatabaseConnection::GetInstance().Initialize(db_path);
}

void DbPlugin::shutdown() {
    spdlog::info("DbPlugin shutting down database connection pool");
}

} // namespace sudharshan::sudharshanmart
