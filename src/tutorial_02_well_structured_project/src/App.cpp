#include "AppComponent.hpp"
#include "controller/MyController.hpp"


#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpRequestHandler.hpp>

#include "oatpp/core/macro/codegen.hpp"


#include "dto/DTOs.hpp"


/**
 * Custom Request Handler
 * */
class Handler : public oatpp::web::server::HttpRequestHandler
{
private:
  // std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;
  OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, m_objectMapper);

public:
  // std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
  //   return ResponseFactory::createResponse(Status::CODE_200, "Hello World!");
  // }
  // Handler(const std:shared_ptr<oatpp::data::mapping::ObjectMapper> &objectMapper) : m_objectMapper(objectMapper) {}
  std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> &request) override
  {
    auto message = MessageDto::createShared();
    message->statusCode = 1024;
    message->message = "Hello DTO!";
    return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
  }
};


void run()
{

  AppComponet components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /* Route GET - "/hello" requests to Handler */
  // router->route("GET", "/hello", std::make_shared<Handler>());
  auto myController = std::make_shared<MyController>();
  myController->addEndpointsToRouter(router);

  /* Get connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

  /* Run server */
  server.run();
}

int main()
{

  /* Init oatpp Environment */
  oatpp::base::Environment::init();

  /* Run App */
  run();

  /* Destroy oatpp Environment */
  oatpp::base::Environment::destroy();

  return 0;
}
