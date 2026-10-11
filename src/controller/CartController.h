#pragma once

#include <drogon/HttpController.h>
#include "controller/BaseController.h"
#include "service/CartService.h"

namespace sudharshan::sudharshanmart {

class CartController : public drogon::HttpController<CartController>, public BaseController {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CartController::GetCart, "/api/v1/cart", drogon::Get, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    ADD_METHOD_TO(CartController::AddItem, "/api/v1/cart/items", drogon::Post, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    ADD_METHOD_TO(CartController::UpdateQuantity, "/api/v1/cart/items/{1}", drogon::Put, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    ADD_METHOD_TO(CartController::RemoveItem, "/api/v1/cart/items/{1}", drogon::Delete, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    ADD_METHOD_TO(CartController::ClearCart, "/api/v1/cart", drogon::Delete, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    METHOD_LIST_END

    void GetCart(const drogon::HttpRequestPtr& req,
                 std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void AddItem(const drogon::HttpRequestPtr& req,
                 std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void UpdateQuantity(const drogon::HttpRequestPtr& req,
                        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                        int64_t product_id);

    void RemoveItem(const drogon::HttpRequestPtr& req,
                    std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                    int64_t product_id);

    void ClearCart(const drogon::HttpRequestPtr& req,
                   std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    static void SetCartService(std::shared_ptr<CartService> service) {
        cart_service_ = std::move(service);
    }

private:
    static std::shared_ptr<CartService> cart_service_;
};

} // namespace sudharshan::sudharshanmart
