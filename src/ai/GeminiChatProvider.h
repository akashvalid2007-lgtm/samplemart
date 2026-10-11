#pragma once

#include "ai/ChatProvider.h"
#include <string>

namespace sudharshan::sudharshanmart {

class GeminiChatProvider : public ChatProvider {
public:
    explicit GeminiChatProvider(std::string api_key = "");

    std::string GetReply(const std::string& user_message,
                         const std::string& context) override;

private:
    std::string api_key_;
};

} // namespace sudharshan::sudharshanmart
