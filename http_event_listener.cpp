#include "http_event_listener.hpp"

using namespace nt::http;

#ifdef SS
#    error SS is already defined
#endif
#define SS nt::utility::string::Stream()

HttpEventListener::HttpEventListener(event_callback handler, void* dispatcher) :
      http_event(nullptr),
      handler(handler),
      dispatcher(dispatcher),
      base(nullptr)
{
}

HttpEventListener::~HttpEventListener()
{
    if (this->http_event != nullptr) {
        evhttp_free(this->http_event);
    }

    if (this->base != nullptr) {
        event_base_free(this->base);
    }
}

void
HttpEventListener::listen(int socket)
{
    this->create_event_base();
    this->create_http_event();
    this->accept_socket(socket);
}

void
HttpEventListener::create_event_base()
{
    struct ::event_base* base = event_init();

    if (base == nullptr) {
        throw std::runtime_error(SS << "");
    }

    this->base = base;
}

void
HttpEventListener::create_http_event()
{
    struct evhttp* httpd = evhttp_new(this->base);

    if (httpd == nullptr) {
        throw std::runtime_error(SS << "");
    }

    this->http_event = httpd;
}

void
HttpEventListener::accept_socket(int socket)
{
    int accept_result = evhttp_accept_socket(this->http_event,
                                             socket);

    if (accept_result != 0) {
        throw std::runtime_error(SS << "");
    }

    evhttp_set_gencb(this->http_event,
                     (void (*)(evhttp_request*, void*))this->handler,
                     this->dispatcher);
}

#undef SS
