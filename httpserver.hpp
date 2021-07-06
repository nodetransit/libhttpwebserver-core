#ifndef FB_HTTP_SERVER_LIBRARY__
#define FB_HTTP_SERVER_LIBRARY__

#include <memory>

namespace fb::http {

class InternalHttpServer;

class HttpServer
{
public:
    int port;
    int connections;
    int threads;

protected:
    std::unique_ptr<InternalHttpServer> server;

public:
    HttpServer();
    ~HttpServer();

    int serve();
};

}

#endif /* FB_HTTP_SERVER_LIBRARY__ */
