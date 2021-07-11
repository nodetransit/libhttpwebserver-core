#ifndef FB_HTTP_INTERNAL_SERVER_LIBRARY__
#define FB_HTTP_INTERNAL_SERVER_LIBRARY__

#include <cstring>
#include <string>
#include <clocale>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <cerrno>

#include <event.h>
#include <evhttp.h>
#include <pthread.h>
#include <magic.h>
#include <dlfcn.h>
#include <tinythread.h>

#include "httpwebserver.hpp"
#include "httpsocket.hpp"
#include "internal_request.hpp"
#include "internal_response.hpp"
#include "request_processor.hpp"
#include "httpstatus.hpp"

namespace nt { namespace http {

class InternalHttpWebServer
{
protected:
    std::unique_ptr <HttpSocket> event;

public:
    InternalHttpWebServer();
    ~InternalHttpWebServer();

    int serve(const int, const int, const int);
    void stop();
protected:
    static void handle(void*, void*);
    static InternalRequest parse_request(void*);

    void process(void*);
};

}}

#endif /* FB_HTTP_INTERNAL_SERVER_LIBRARY__ */
