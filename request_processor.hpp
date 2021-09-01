#ifndef FB_HTTP_REQUEST_PROCESSOR_LIBRARY__
#define FB_HTTP_REQUEST_PROCESSOR_LIBRARY__

#include <sstream>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <cstdio>

#include <event.h>
#include <evhttp.h>

#include <interfaces/guest.hpp>
#include <macros/scope_guard.hpp>
#include <macros/repeat_until.hpp>

#include "internal_request.hpp"
#include "utility/string.hpp"
#include "utility/nullcoalesce.hpp"
#include "stream/memory_file.hpp"
#include "error.hpp"

namespace nt { namespace http {

using nt::http::interfaces::Guest;

class InternalRequest;

class RequestProcessor :
      public Guest<InternalRequest>
{
public:
    std::string                                           method;
    std::unordered_map<std::string, std::string>          headers;
    std::unordered_map<std::string, std::string>          post_data;
    std::unordered_map<std::string, std::string>          query_data;
    std::unordered_map<std::string, std::string>          cookies;
    std::unordered_map<std::string, nt::interfaces::File> files;

private:
    evhttp_request* request;

public:
    RequestProcessor();
    ~RequestProcessor() = default;

    void visit(InternalRequest* host);

protected:
    void parse(evhttp_request*);
    void parse_method();
    void parse_uri();
    void parse_headers();
    void parse_post_data();
    void parse_files();

};

}}

#endif /* FB_HTTP_REQUEST_PROCESSOR_LIBRARY__ */
