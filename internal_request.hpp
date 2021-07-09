#ifndef FB_HTTP_INTERNAL_REQUEST_LIBRARY__
#define FB_HTTP_INTERNAL_REQUEST_LIBRARY__

#include <sstream>
#include <unordered_map>
#include <algorithm>

#include <interfaces/host.hpp>
#include <interfaces/request.hpp>

#include <event.h>
#include <evhttp.h>

namespace nt { namespace http {

using nt::http::interfaces::Guest;
using nt::http::interfaces::Request;

class InternalRequest :
      public Request
{
public:
    evhttp_request* request;
    std::string error;

public:
    InternalRequest();
    InternalRequest(evhttp_request*);
    ~InternalRequest();

    bool is_valid();
    std::string get_error();

    HOST(accept);
};

}}

#endif /* FB_HTTP_INTERNAL_REQUEST_LIBRARY__ */
