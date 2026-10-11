#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace sudharshan::sudharshanmart {

struct ChatRequestDto {
    std::string message;
};

struct ChatResponseDto {
    std::string reply;

    [[nodiscard]] nlohmann::json ToJson() const {
        return nlohmann::json{
            {"reply", reply}
        };
    }
};

} // namespace sudharshan::sudharshanmart
