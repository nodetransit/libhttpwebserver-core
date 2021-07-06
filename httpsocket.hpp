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
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>

#include "string_stream.hpp"
#include "http_event_listener.hpp"

#include <errno.h>
namespace fb::http {

typedef void (* event_callback)(void*, void*);

class HttpSocket
{
private:
    int                             socket;
    std::vector <pthread_t>         threads;
    std::vector<HttpEventListener*> listeners;

public:
    HttpSocket();
    ~HttpSocket();

    void bind_http_port(const int, const int);
    void create_threads(const int, event_callback, void*);

protected:
    static void* dispatch(void*);

private:
    void create_socket();
    void set_socket_options();
    void bind_socket(const int);
    void listen(const int);
    void set_access_mode();
};

}

#endif /* FB_REQUEST_EVENT_LIBRARY__ */
