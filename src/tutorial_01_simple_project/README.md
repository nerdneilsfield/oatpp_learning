# Simple Project

这一节主要是一些基本的例子，让大家对 `oatpp` 有一些非常直观的概念。


## Demo1

这个例子的关键介绍了一个 `oatpp` 服务端程序应该有哪些部分：

``` c++
auto router = oatpp::web::server::HttpRouter::createShared();
auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});
oatpp::network::Server server(connectionProvider, connectionHandler);
```

一个 `oatpp::network::Server` 需要：

1. `oatpp::web::server::HttpConnectionHandler`
2. `oatpp::network::tcp::server::ConnectionProvider`

同时需要一个 `oatpp::web::server::HttpRouter` 来处理连接路由的问题


这些都包含在如下的头文件里面:

``` c++
#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
```


每个类的具体功能如下：

-   [HttpRouter](https://oatpp.io/api/latest/oatpp/web/server/HttpRouter/) - Router of HTTP requests. It maps URLs to endpoint handlers. Our app has no endpoints declared so far hence the server will always return `404 not found`.
-   [HttpConnectionHandler](https://oatpp.io/api/latest/oatpp/web/server/HttpConnectionHandler/) - This is a simple HTTP connection handler. It handles incoming connections in a multi threaded manner, creating one thread per each connection. 这是一个简单的HTTP连接处理程序。它以多线程的方式处理传入的连接，为每个连接创建一个线程。(创建线程的开销应该比 golang 之类提供的协程高吧)
-   [ConnectionProvider](https://oatpp.io/api/latest/oatpp/network/tcp/server/ConnectionProvider/) - Provider of `TCP` connections. It binds to a specified port. 在指定的 `endpoint` 和 `port` 建立连接，这是使用的是 TCP4。
-   [Server](https://oatpp.io/api/latest/oatpp/network/Server/) - Server runs a loop which takes connections from `ConnectionProvider` and passes them to `ConnectionHandler`.  Server 就是一个 eventloop 目的就是通过 `ConnectionProvider` 来建立连接，并调用 `ConnectionHandler` 来处理 `request` 。
