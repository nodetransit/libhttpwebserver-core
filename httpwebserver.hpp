#ifndef FB_HTTP_SERVER_LIBRARY__
#define FB_HTTP_SERVER_LIBRARY__

#include <memory>

namespace nt { namespace http {

class InternalHttpWebServer;

class HttpWebServer
{
public:
    int port;
    int connections;
    int threads;

protected:
    std::unique_ptr<InternalHttpWebServer> server;

public:
    HttpWebServer();
    ~HttpWebServer();

    int serve();
    void stop();
};

}}

#endif /* FB_HTTP_SERVER_LIBRARY__ */
