#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpRequestHandler.hpp>

#include "oatpp/core/macro/codegen.hpp"


/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

class MessageDto : public oatpp::DTO
{
  DTO_INIT(MessageDto, DTO);

  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)


/**
 * Custom Request Handler
 * */
class Handler : public oatpp::web::server::HttpRequestHandler
{
private:
  std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;

public:
  // std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
  //   return ResponseFactory::createResponse(Status::CODE_200, "Hello World!");
  // }
  Handler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper> &objectMapper) : m_objectMapper(objectMapper) {}
  std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
    auto message = MessageDto::createShared();
    message->statusCode = 1024;
    message->message = "Hello DTO!";
    return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
  }
};


void run()
{

  /* Create a json object mapper */
  auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

  /* Create Router for HTTP requests routing */
  auto router = oatpp::web::server::HttpRouter::createShared();

  /* add handler for router '/hello' */
  router->route("GET", "/hello", std::make_shared<Handler>(objectMapper));

  /* Create HTTP connection handler with router */
  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

  /* Create TCP connection provider */
  auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({ "0.0.0.0", 8000, oatpp::network::Address::IP_4 });

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
