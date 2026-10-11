#include "repository/RepositoryFactory.h"
#include "repository/SqliteUserRepository.h"
#include "repository/SqliteProductRepository.h"
#include "repository/SqliteCartRepository.h"
#include "repository/SqliteOrderRepository.h"
#include "repository/SqliteReviewRepository.h"

namespace sudharshan::sudharshanmart {

std::unique_ptr<IUserRepository> RepositoryFactory::CreateUserRepository(DatabaseConnection& db_conn) {
    return std::make_unique<SqliteUserRepository>(db_conn);
}

std::unique_ptr<IProductRepository> RepositoryFactory::CreateProductRepository(DatabaseConnection& db_conn) {
    return std::make_unique<SqliteProductRepository>(db_conn);
}

std::unique_ptr<ICartRepository> RepositoryFactory::CreateCartRepository(DatabaseConnection& db_conn) {
    return std::make_unique<SqliteCartRepository>(db_conn);
}

std::unique_ptr<IOrderRepository> RepositoryFactory::CreateOrderRepository(DatabaseConnection& db_conn) {
    return std::make_unique<SqliteOrderRepository>(db_conn);
}

std::unique_ptr<IReviewRepository> RepositoryFactory::CreateReviewRepository(DatabaseConnection& db_conn) {
    return std::make_unique<SqliteReviewRepository>(db_conn);
}

} // namespace sudharshan::sudharshanmart
