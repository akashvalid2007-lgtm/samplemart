#pragma once

#include <drogon/plugins/Plugin.h>
#include "repository/DatabaseConnection.h"

namespace sudharshan::sudharshanmart {

/**
 * @brief Drogon Plugin lifecycle owner for the database connection singleton.
 */
class DbPlugin : public drogon::Plugin<DbPlugin> {
public:
    DbPlugin() = default;

    void initAndStart(const Json::Value& config) override;
    void shutdown() override;

    static DatabaseConnection& GetDbConnection() {
        return DatabaseConnection::GetInstance();
    }
};

} // namespace sudharshan::sudharshanmart
