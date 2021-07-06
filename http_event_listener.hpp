#ifndef FB_HTTP_REQUEST_LISTENER_LIBRARY__
#define FB_HTTP_REQUEST_LISTENER_LIBRARY__

#include <event.h>
#include <evhttp.h>
#include <errno.h>

#include "string_stream.hpp"

namespace fb::http {

typedef void (* event_callback)(void*, void*);

class HttpEventListener
{
private:
    evhttp* http_event;
    event_callback handler;
    void* dispatcher;

public:
    ::event_base* base;

public:
    HttpEventListener(event_callback, void*);
    ~HttpEventListener();

    void listen(int);

private:
    void create_event_base();
    void create_http_event();
    void accept_socket(int);
};

}

#endif /* FB_HTTP_REQUEST_LISTENER_LIBRARY__ */
