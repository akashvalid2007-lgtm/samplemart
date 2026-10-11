#pragma once

#include <drogon/HttpController.h>
#include "controller/BaseController.h"
#include "service/OrderService.h"

namespace sudharshan::sudharshanmart {

class OrderController : public drogon::HttpController<OrderController>, public BaseController {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(OrderController::Checkout, "/api/v1/orders/checkout", drogon::Post, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    ADD_METHOD_TO(OrderController::GetBuyerOrders, "/api/v1/orders/buyer", drogon::Get, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    ADD_METHOD_TO(OrderController::GetSellerOrders, "/api/v1/orders/seller", drogon::Get, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    ADD_METHOD_TO(OrderController::GetSellerDashboard, "/api/v1/orders/seller/dashboard", drogon::Get, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    ADD_METHOD_TO(OrderController::GetOrder, "/api/v1/orders/{1}", drogon::Get, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    ADD_METHOD_TO(OrderController::UpdateOrderStatus, "/api/v1/orders/{1}/status", drogon::Put, "sudharshan::sudharshanmart::LoggingFilter", "sudharshan::sudharshanmart::AuthFilter", "sudharshan::sudharshanmart::CorsFilter");
    METHOD_LIST_END

    void Checkout(const drogon::HttpRequestPtr& req,
                  std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void GetBuyerOrders(const drogon::HttpRequestPtr& req,
                        std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void GetSellerOrders(const drogon::HttpRequestPtr& req,
                         std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void GetSellerDashboard(const drogon::HttpRequestPtr& req,
                            std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void GetOrder(const drogon::HttpRequestPtr& req,
                  std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                  int64_t order_id);

    void UpdateOrderStatus(const drogon::HttpRequestPtr& req,
                           std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                           int64_t order_id);

    static void SetOrderService(std::shared_ptr<OrderService> service) {
        order_service_ = std::move(service);
    }

private:
    static std::shared_ptr<OrderService> order_service_;
};

} // namespace sudharshan::sudharshanmart
