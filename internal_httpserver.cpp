#include "internal_httpserver.hpp"

#include <dlfcn.h>
#include "macros/finally.hpp"
#include "macros/nullcoalesce.hpp"

#include <chrono>

#include "interfaces/guest.hpp"

using namespace fb::http;

static std::string
__get_mimetype__(std::string filename)
{
    void* handler = dlopen("./libmagic.so", RTLD_NOW);

    if (handler == nullptr) {
        throw std::runtime_error("unable to load libmagic");
    }

    magic_t magic = magic_open(MAGIC_MIME_TYPE);

    magic_load(magic, nullptr);
    magic_compile(magic, nullptr);
    std::string mimetype(magic_file(magic, filename.c_str()));

    if (mimetype == "text/plain") {
        // mimetype = map_text_plain(filename);
    }

    return mimetype;
}

InternalHttpServer::InternalHttpServer() :
      event(std::make_unique<HttpSocket>())
{
}

InternalHttpServer::~InternalHttpServer()
{
}

int
InternalHttpServer::serve(const int port,
                          const int num_threads,
                          const int max_connections)
{
    this->event->bind_http_port(port, max_connections);
    this->event->create_threads(num_threads,
                                InternalHttpServer::handle,
                                this);

    return EXIT_SUCCESS;
}

void
InternalHttpServer::handle(void* r, void* dispatcher)
{
    struct evhttp_request* request = (evhttp_request*)r;

    if (request == nullptr) {
        return;
    }

    InternalHttpServer* server = (InternalHttpServer*)dispatcher;

    try {
        server->process(request);
    } catch (...) {
        evhttp_clear_headers(evhttp_request_get_output_headers(request));
        evhttp_send_error(request,
                          status::code_internal_server_error,
                          status::get_reason(status::code_internal_server_error).c_str());
    }
}

void
InternalHttpServer::process(void* r)
{
    struct evhttp_request* request = (evhttp_request*)r;

    if (request == nullptr) {
        return;
    }

    InternalRequest ir = InternalHttpServer::parse_request(r);

    setlocale(LC_ALL, "C.UTF-8");

    struct evbuffer* buf = evbuffer_new();

    if (buf == nullptr) {
        evhttp_send_error(request, HTTP_INTERNAL, "internal server error");
        return;
    }

    std::string header    = "<!DOCTYPE html>"
                            "<html lang='en'>"
                            "<head>"
                            "<meta charset='UTF-8'>"
                            "</head>"
                            "<body>"
                            "<script type='text/javascript' src='/test.js'></script>"
                            "<img src='/img.jpg' width='100' />"
                            "<video autoplay controls><source src='/video.mp4' type='video/mp4' /></video>";
    std::string uri_plain = evhttp_request_uri(request);
    std::string uri       = evhttp_decode_uri(uri_plain.c_str());

    std::time_t now = std::time(0);
    char* cc          = ctime(&now);

    evbuffer_add(buf, header.c_str(), header.length());
    evbuffer_add_printf(buf, "<p>Requested: %s %s</p>", uri.c_str(), cc);

    evbuffer_add_printf(buf, "<h1>マルチバイト文字列</h1>\n");

    std::wstring s2(L"<h1>wchar_t 文字列</h1>\n");
    evbuffer_add_printf(buf, "%ls", s2.c_str());

    std::wstring headers_h4(L"<h1>wcstombs 変換</h1>\n");
    int          size = headers_h4.length() * sizeof(wchar_t) + 2;
    char         wbuf[size];
    int          cx   = wcstombs(wbuf, headers_h4.c_str(), size);
    evbuffer_add(buf, wbuf, cx);

    evbuffer_add_printf(buf, "<pre>");

    for (auto& hd: ir.headers) {
        evbuffer_add_printf(buf, "\t%s\t\t: %s\n", hd.first.c_str(), hd.second.c_str());
    }

    evbuffer_add_printf(buf, "</pre>");

    evbuffer_add_printf(buf, "<h1>ポスト</h1>");
    evbuffer_add_printf(buf, "<pre>");

    for (auto& pd: ir.post_data) {
        evbuffer_add_printf(buf, "\t%s\t\t: %s\n", pd.first.c_str(), pd.second.c_str());
    }

    evbuffer_add_printf(buf, "</pre>");

    std::string form = "<form action='/upload' method='POST'>"
                       "<input type='text' name='user' />"
                       "<input type='password' name='secret' />"
                       "<textarea name='message'></textarea>"
                       "<input name='fsubmit' type='submit' value='send' />"
                       "</form>"
                       "<form action='/upload' method='POST' enctype='multipart/form-data' >"
                       "<input type='text' name='user' />"
                       "<input type='password' name='secret' />"
                       "<input type='file' name='key' />"
                       "<input name='mp_submit' type='submit' value='send' />"
                       "</form>";
    evbuffer_add_printf(buf, form.c_str());

    evbuffer_add_printf(buf, "</body></html>");

    evhttp_add_header(evhttp_request_get_output_headers(request), "Content-Type", "text/html; charset=UTF-8");
    evhttp_send_reply(request,
                      status::code_ok,
                      status::get_reason(status::code_ok).c_str(),
                      buf);
}

InternalRequest
InternalHttpServer::parse_request(void* r)
{
    auto processor = std::make_unique<RequestProcessor>();
    auto request   = InternalRequest((evhttp_request*)r);

    request.accept<RequestProcessor>(processor.get());

    // auto headers = InternalHttpServer::parse_headers(r);
    // auto post    = InternalHttpServer::parse_post_data(r, headers);

    return request;
}


