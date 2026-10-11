#include <drogon/drogon.h>
#include <spdlog/spdlog.h>
#include <cstdlib>
#include <memory>

#include "repository/DatabaseConnection.h"
#include "repository/RepositoryFactory.h"
#include "service/MigrationService.h"
#include "service/AuthService.h"
#include "service/ProductService.h"
#include "service/CartService.h"
#include "service/OrderService.h"
#include "service/ReviewService.h"
#include "service/ChatService.h"
#include "ai/ChatProviderFactory.h"

#include "controller/AuthController.h"
#include "controller/ProductController.h"
#include "controller/CartController.h"
#include "controller/OrderController.h"
#include "controller/ReviewController.h"
#include "controller/AdminController.h"
#include "controller/ChatController.h"

using namespace sudharshan::sudharshanmart;

int main(int argc, char* argv[]) {
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    spdlog::info("Starting SudharshanMart C++20 Server (Owner: Sudharshan)...");

    // 1. Initialize SQLite Database Connection (Singleton)
    std::string db_file = "sudharshanmart.db";
    DatabaseConnection& db_conn = DatabaseConnection::GetInstance();
    db_conn.Initialize(db_file);

    // 2. Run Database Migrations and apply initial seed data
    MigrationService migration_service(db_conn);
    migration_service.RunMigrations("db/migrations", "db/seed.sql");

    // 3. Instantiate Repositories via Factory Pattern (Dependency Inversion)
    std::shared_ptr<IUserRepository> user_repo = RepositoryFactory::CreateUserRepository(db_conn);
    std::shared_ptr<IProductRepository> product_repo = RepositoryFactory::CreateProductRepository(db_conn);
    std::shared_ptr<ICartRepository> cart_repo = RepositoryFactory::CreateCartRepository(db_conn);
    std::shared_ptr<IOrderRepository> order_repo = RepositoryFactory::CreateOrderRepository(db_conn);
    std::shared_ptr<IReviewRepository> review_repo = RepositoryFactory::CreateReviewRepository(db_conn);

    // 4. Instantiate Services (Pure C++ business rules, constructor injected)
    auto auth_service = std::make_shared<AuthService>(user_repo);
    auto product_service = std::make_shared<ProductService>(product_repo);
    auto cart_service = std::make_shared<CartService>(cart_repo, product_repo);
    auto order_service = std::make_shared<OrderService>(order_repo, cart_repo);
    auto review_service = std::make_shared<ReviewService>(review_repo, product_repo);

    // 5. Instantiate AI Chatbot Provider (Mock or Gemini via Factory)
    std::string ai_provider_type = "mock";
    const char* env_provider = std::getenv("AI_CHATBOT_PROVIDER");
    if (env_provider) {
        ai_provider_type = env_provider;
    }
    std::shared_ptr<ChatProvider> chat_provider = ChatProviderFactory::CreateProvider(ai_provider_type);
    auto chat_service = std::make_shared<ChatService>(chat_provider);

    // 6. Wire Dependencies into Controllers
    AuthController::SetAuthService(auth_service);
    ProductController::SetProductService(product_service);
    CartController::SetCartService(cart_service);
    OrderController::SetOrderService(order_service);
    ReviewController::SetReviewService(review_service);
    AdminController::InitializeDependencies(user_repo, order_service, product_service);
    ChatController::SetChatService(chat_service);

    // 7. Drogon Server Configuration
    std::string port_str = "8080";
    const char* env_port = std::getenv("PORT");
    if (env_port) {
        port_str = env_port;
    }
    uint16_t port = static_cast<uint16_t>(std::stoi(port_str));

    spdlog::info("Configuring Drogon listener on 0.0.0.0:{}", port);
    drogon::app()
        .addListener("0.0.0.0", port)
        .setDocumentRoot("./public")
        .enableSession(3600) // Explicit 1-hour idle session timeout
        .setClientMaxBodySize(10 * 1024 * 1024);

    spdlog::info("SudharshanMart is ready! Serving web frontend and API at http://localhost:{}", port);
    drogon::app().run();

    return 0;
}
