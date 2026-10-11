#pragma once

#include <memory>
#include "repository/IUserRepository.h"
#include "repository/IProductRepository.h"
#include "repository/ICartRepository.h"
#include "repository/IOrderRepository.h"
#include "repository/IReviewRepository.h"
#include "repository/DatabaseConnection.h"

namespace sudharshan::sudharshanmart {

/**
 * @brief Factory for instantiating repository implementations.
 * Satisfies the Factory Design Pattern requirement returning std::unique_ptr<Interface>.
 */
class RepositoryFactory {
public:
    static std::unique_ptr<IUserRepository> CreateUserRepository(DatabaseConnection& db_conn);
    static std::unique_ptr<IProductRepository> CreateProductRepository(DatabaseConnection& db_conn);
    static std::unique_ptr<ICartRepository> CreateCartRepository(DatabaseConnection& db_conn);
    static std::unique_ptr<IOrderRepository> CreateOrderRepository(DatabaseConnection& db_conn);
    static std::unique_ptr<IReviewRepository> CreateReviewRepository(DatabaseConnection& db_conn);
};

} // namespace sudharshan::sudharshanmart
