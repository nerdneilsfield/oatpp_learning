#ifndef APPCOMPONENT_H_
#define APPCOMPONENT_H_
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/core/macro/component.hpp"

class AppComponet
{
public:
  // crete connect provider
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnctionProvider)
  ([] {
    return oatpp::network::tcp::server::ConnectionProvider::createShared({ "0.0.0.0", 8000, oatpp::network::Address::IP_4 });
  }());
  // create router component
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
  ([] {
    return oatpp::web::server::HttpRouter::createShared();
  }());
  // create Connection Handler component which uses Router component to route requests
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)
  ([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    return oatpp::web::server::HttpConnectionHandler::createShared(router);
  }());
  // create objectmapper component to serialize/deserialize DTOs in Controller's API
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
  ([] {
    return oatpp::parser::json::mapping::ObjectMapper::createShared();
  }());
};


#endif// APPCOMPONENT_H_
