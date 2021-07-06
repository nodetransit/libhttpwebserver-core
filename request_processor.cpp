#include "request_processor.hpp"

using namespace fb::http;

RequestProcessor::RequestProcessor() :
      request(nullptr)
{
}

RequestProcessor::~RequestProcessor()
{
}

void
RequestProcessor::parse(evhttp_request*)
{
    if(this->request == nullptr) {
        return;
    }

    this->parse_headers();
}

void
RequestProcessor::parse_method()
{
    if(this->request == nullptr) {
        return;
    }

    evhttp_cmd_type type = evhttp_request_get_command(this->request);

    switch (type) {
    case EVHTTP_REQ_GET     :
        this->method = "GET";
        break;
    case EVHTTP_REQ_POST    :
        this->method = "POST";
        break;
    case EVHTTP_REQ_HEAD    :
        this->method = "HEAD";
        break;
    case EVHTTP_REQ_PUT     :
        this->method = "PUT";
        break;
    case EVHTTP_REQ_DELETE  :
        this->method = "DELETE";
        break;
    case EVHTTP_REQ_OPTIONS :
        this->method = "OPTIONS";
        break;
    case EVHTTP_REQ_TRACE   :
        this->method = "TRACE";
        break;
    case EVHTTP_REQ_CONNECT :
        this->method = "CONNECT";
        break;
    case EVHTTP_REQ_PATCH   :
        this->method = "PATCH";
        break;
        // case EVHTTP_REQ_PROPFIND:
        //     this->method =  "PROPFIND";
        //     break;
        // case EVHTTP_REQ_PROPPATCH:
        //     this->method =  "PROPPATCH";
        //     break;
        // case EVHTTP_REQ_MKCOL   :
        //     this->method =  "MKCOL";
        //     break;
        // case EVHTTP_REQ_LOCK    :
        //     this->method =  "LOCK";
        //     break;
        // case EVHTTP_REQ_UNLOCK  :
        //     this->method =  "UNLOCK";
        //     break;
        // case EVHTTP_REQ_COPY    :
        //     this->method =  "COPY";
        //     break;
        // case EVHTTP_REQ_MOVE    :
        //     this->method =  "MOVE";
        //     break;
    default:
        // this->method =  "NULL";
        throw std::runtime_error("invalid method");
    }
}

void
RequestProcessor::parse_headers()
{
    if(this->request == nullptr) {
        return;
    }

    evkeyvalq* req_headers = evhttp_request_get_input_headers(this->request);

    if (req_headers == nullptr) {
        this->headers = {};
        return;
    }

    evkeyval* cur = req_headers->tqh_first;

    std::unordered_map <std::string, std::string> headers = {};

    do {
        char* key = cur->key;
        char* val = cur->value;

        headers.insert({key, val});

        cur = cur->next.tqe_next;

    } while (cur != nullptr);

    this->headers = headers;
}

void
RequestProcessor::parse_post_data()
{
    this->post_data = {};

    if(this->request == nullptr) {
        return;
    }

    if (this->method != "POST" || this->method != "PUT" || this->method != "PATCH") {
        return;
    }

    if (this->headers.find("Content-Type") != this->headers.end()) {
        std::string post_data = (char*)evbuffer_pullup(this->request->input_buffer, -1);

        if (this->headers["Content-Type"] == "application/x-www-form-urlencoded") {
            std::stringstream ss(post_data);
            std::string       item;

            std::unordered_map <std::string, std::string> map = {};

            while (std::getline(ss, item, '&')) {
                int         index = item.find('=', 0);
                std::string key   = evhttp_decode_uri(item.substr(0, index).c_str());
                std::string value = evhttp_decode_uri(item.substr(index + 1, -1).c_str());

                map.insert({key, value});
            }

            this->post_data = map;

        } else if (this->headers["Content-Type"] == "multipart/form-data") {
            this->post_data = {};

        }
    }
}

void
RequestProcessor::visit(InternalRequest* host)
{
    if(host->request == nullptr) {
        return;
    }

    this->parse(host->request);
}

