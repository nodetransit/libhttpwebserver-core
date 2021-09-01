#ifndef FB_REQUEST_EVENT_LIBRARY__
#define FB_REQUEST_EVENT_LIBRARY__

#include <vector>
#include <event.h>
#include <evhttp.h>
#include <cstring>
#include <stdexcept>
#include <vector>

#include <event.h>
#include <evhttp.h>
#include <tinythread.h>
#include <fast_mutex.h>
#include <fcntl.h>
#include <cerrno>
#include <utility>

#include "utility/string_stream.hpp"
#include "http_event_listener.hpp"

namespace nt { namespace http {

typedef void (* event_callback)(void*, void*);

class HttpSocket
{
private:
    int  socket;
    bool stopped;

    std::vector<std::pair<HttpEventListener*, tthread::thread*>> handlers;

public:
    HttpSocket();
    ~HttpSocket();

    void bind_http_port(const int, const int);
    void create_threads(const unsigned int, event_callback, void*);

    void close();
protected:
    static void dispatch(void*);

private:
    void create_socket();
    void set_socket_options();
    void bind_socket(const int);
    void listen(const int);
    void set_access_mode();
};

}}

#endif /* FB_REQUEST_EVENT_LIBRARY__ */
