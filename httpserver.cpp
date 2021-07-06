#include <memory>
#include <stdexcept>

#include "httpserver.hpp"
#include "internal_httpserver.hpp"
#include "string_stream.hpp"

using namespace fb::http;

typedef fb::utility::StringStream SS;

HttpServer::HttpServer() :
      port(-1),
      connections(-1),
      threads(-1),
      server(std::make_unique<InternalHttpServer>()) // server(new InternalHttpServer())
{
}

HttpServer::~HttpServer()
{
}

int
HttpServer::serve()
{
    if (this->port <= 0) {
        throw std::runtime_error(SS() << "Invalid or unspecified port: " << this->port);
    }

    if (this->connections <= 0) {
        throw std::runtime_error(SS() << "Invalid or unspecified number of connections: " << this->connections);
    }

    if (this->threads <= 0) {
        throw std::runtime_error(SS() << "Invalid or unspecified number of threads: " << this->threads);
    }

    return this->server->serve(this->port,
                               this->threads,
                               this->connections);
}
