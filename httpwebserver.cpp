#include <memory>
#include <stdexcept>

#include "httpwebserver.hpp"
#include "internal_httpwebserver.hpp"
#include "utility/string_stream.hpp"

using namespace nt::http;

typedef nt::utility::string::Stream SS;

HttpWebServer::HttpWebServer() :
      port(-1),
      connections(-1),
      threads(-1),
      server(std::make_unique<InternalHttpWebServer>()) // server(new InternalHttpServer())
{
}

HttpWebServer::~HttpWebServer()
{
}

void
HttpWebServer::serve()
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

    this->server->serve(this->port,
                        this->threads,
                        this->connections);
}

void
HttpWebServer::stop()
{
    this->server->stop();
}

// void
// HttpWebServer::wait()
// {
//     this->server->wait();
// }
