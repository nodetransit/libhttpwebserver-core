#ifndef FB_HTTP_INTERNAL_SERVER_LIBRARY__
#define FB_HTTP_INTERNAL_SERVER_LIBRARY__

#include <cstring>
#include <string>
#include <clocale>
#include <string>
#include <unordered_map>
#include <cstdlib>

#include <event.h>
#include <evhttp.h>
#include <pthread.h>
#include <errno.h>
#include <magic.h>
#include <dlfcn.h>

#include "httpserver.hpp"
#include "httpsocket.hpp"
#include "internal_request.hpp"
#include "internal_response.hpp"
#include "request_processor.hpp"
#include "httpstatus.hpp"

namespace fb::http {

class InternalHttpServer
{
protected:
    std::unique_ptr <HttpSocket> event;

public:
    InternalHttpServer();
    ~InternalHttpServer();

    int serve(const int, const int, const int);
protected:
    static void handle(void*, void*);
    static InternalRequest parse_request(void*);
    static std::string get_request_type(void*);
    static std::unordered_map <std::string, std::string> parse_headers(void*);
    static std::unordered_map <std::string, std::string> parse_post_data(void*, std::unordered_map <std::string, std::string>);
    static std::unordered_map <std::string, std::string> parse_query_string(void*);
    static std::unordered_map <std::string, std::string> parse_cookies(void*);
    static std::unordered_map <std::string, std::string> parse_files(void*);

    void process(void*);
};

}

#endif /* FB_HTTP_INTERNAL_SERVER_LIBRARY__ */
