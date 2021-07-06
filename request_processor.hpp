#ifndef FB_HTTP_REQUEST_PROCESSOR_LIBRARY__
#define FB_HTTP_REQUEST_PROCESSOR_LIBRARY__

#include <sstream>
#include <unordered_map>
#include <vector>

#include <event.h>
#include <evhttp.h>

#include "interfaces/guest.hpp"
#include "internal_request.hpp"

namespace fb::http {

using fb::http::interfaces::Guest;

class InternalRequest;

class RequestProcessor :
      public Guest<InternalRequest>
{
public:
    std::string                                   method;
    std::unordered_map <std::string, std::string> headers;
    std::unordered_map <std::string, std::string> post_data;
    std::unordered_map <std::string, std::string> query;
    std::unordered_map <std::string, std::string> cookies;
    std::unordered_map <std::string, std::string> files;

private:
    evhttp_request* request;

public:
    RequestProcessor();
    ~RequestProcessor();

    void visit(InternalRequest* host);

protected:
    void parse(evhttp_request*);
    void parse_method();
    void parse_headers();
    void parse_post_data();
    void parse_query_string();
    void parse_cookies();
    void parse_files();

};

}

#endif /* FB_HTTP_REQUEST_PROCESSOR_LIBRARY__ */
