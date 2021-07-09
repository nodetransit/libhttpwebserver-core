#ifndef FB_HTTP_REQUEST_LIBRARY__
#define FB_HTTP_REQUEST_LIBRARY__

#include <sstream>
#include <unordered_map>
#include <algorithm>

#include <event.h>
#include <evhttp.h>

namespace nt { namespace http {


class Request
{
private:
public:
    std::string                                   method;
    std::string                                   body;
    std::unordered_map <std::string, std::string> headers;
    std::unordered_map <std::string, std::string> post_data;
    std::string                                   uri;
    std::string                                   query_string;
    std::unordered_map <std::string, std::string> query_data;
    std::unordered_map <std::string, std::string> cookies;
    std::unordered_map <std::string, std::string> files;

public:
    Request();
    ~Request();

};

}}

#endif /* FB_INTERNAL_REQUEST_LIBRARY__ */
