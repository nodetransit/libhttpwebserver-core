#include "request_processor.hpp"

using namespace nt::http;

RequestProcessor::RequestProcessor() :
      request(nullptr)
{
}

void
RequestProcessor::parse(evhttp_request* http_request)
{
    if (http_request == nullptr) {
        throw std::logic_error("");
    }

    this->request = http_request;

    this->parse_method();
    this->parse_headers();
    this->parse_post_data();

    //         std::string uri_plain = evhttp_request_uri(req);
    //         // char *evhttp_encode_uri(const char *uri);
    //         // std::string url       = evhttp_decode_uri(uri_plain.c_str());
    //         struct evhttp_uri* uri = evhttp_uri_parse(req->uri);
    //         // std::string query = evhttp_uri_get_query(uri);
    //
    //         std::string host     = NULLXX(evhttp_uri_get_host(uri), "");
    //         std::string path     = evhttp_decode_uri(NULLXX(evhttp_uri_get_path(uri), ""));
    //         std::string fragment = NULLXX(evhttp_uri_get_fragment(uri), "");
    //         std::string query    = NULLXX(evhttp_uri_get_query(uri), "");
    //         std::string scheme   = NULLXX(evhttp_uri_get_scheme(uri), "");
    //         std::string userinfo = NULLXX(evhttp_uri_get_userinfo(uri), "");
    //         evhttp_uri_free(uri);
}

void
RequestProcessor::parse_method()
{
    if (this->request == nullptr) {
        throw std::logic_error("");
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
    if (this->request == nullptr) {
        throw std::logic_error("");
    }

    evkeyvalq* req_headers = evhttp_request_get_input_headers(this->request);

    if (req_headers == nullptr) {
        this->headers = {};
        return;
    }

    evkeyval* cur = req_headers->tqh_first;

    std::unordered_map<std::string, std::string> header_map = {};

    do {
        char* key = cur->key;
        char* val = cur->value;

        header_map.emplace(key, val);

        cur = cur->next.tqe_next;

    } while (cur != nullptr);

    this->headers = header_map;
}

inline namespace {
std::unordered_map<std::string, std::string>
parse_url_encoded_form(const std::string& post_data, const std::string& content_type)
{
    std::unordered_map<std::string, std::string> map = {};

    using namespace nt::utility::string;

    for (auto& item : split(post_data, "&")) {
        int         index = item.find('=', 0);
        std::string key   = html_decode(item.substr(0, index));
        std::string value = html_decode(item.substr(index + 1, -1));

        map.emplace(key, value);
    }

    return map;
}

std::string
parse_multipart_boundary(const std::string& content_type)
{
    std::stringstream ss(content_type);
    std::string       item;
    std::string       boundary;

    while (std::getline(ss, item, ';')) {
        using namespace nt::utility::string;

        int index = item.find('=', 0);

        std::string key = tolower(trim(item.substr(0, index)));

        std::string value = index < 0 ?
                            "" :
                            trim(item.substr(index + 1, -1));

        if (key == "boundary") {
            if (value.empty()) {
                throw std::logic_error("");
            }

            if (value[0] == '"' || value[0] == '\'') {
                boundary = value.substr(1, value.length() - 2);
            } else {
                boundary = value;
            }


            break;
        }
    }

    if (boundary.empty()) {
        throw std::logic_error("");
    }

    return boundary;
}

std::pair<std::string, std::string>
parse_multipart_form_data(std::string& part_data)
{
    using nt::utility::string::getline;
    using nt::utility::string::ltrim;

    const std::string crlf = "\r\n";

    std::string header = getline(part_data, crlf);
    getline(part_data, crlf);

    if (part_data.length() >= 2) {
        part_data.erase(part_data.length() - 2, 2);
    }

    std::string body = part_data;

    std::string key   = header;
    std::string value = body;

    return {key, value};
}

/**
 * @brief
 * @param post_data
 * @param content_type
 * @see https://datatracker.ietf.org/doc/html/rfc2046#section-5.1.1
 * @return
 */
std::unordered_map<std::string, std::string>
parse_multipart_form(std::string post_data, const std::string& content_type)
{
    std::unordered_map<std::string, std::string> post_map = {};

    std::string boundary = "--" + parse_multipart_boundary(content_type);

    do {
        using nt::utility::string::getline;
        using nt::utility::string::ltrim;

        std::string part_data = ltrim(getline(post_data, boundary));

        if (!part_data.empty()) {
            post_map.insert(parse_multipart_form_data(part_data));
        }

    } while (!post_data.empty() && post_data != "--\r\n");

    return post_map;
}

std::unordered_map<std::string, std::string>
parse_multipart_mixed_body(const std::string& post_data, const std::string& content_type)
{
    return {};
}

std::unordered_map<std::string, std::string>
parse_plain_text_body(const std::string& post_data, const std::string& content_type)
{
    std::unordered_map<std::string, std::string> map = {
          {"body", post_data},
    };

    return map;
}
}

void
RequestProcessor::parse_post_data()
{
    this->post_data = {};

    if (this->request == nullptr) {
        return;
    }

    if (this->method != "POST" && this->method != "PUT" && this->method != "PATCH") {
        return;
    }

    if (this->headers.find("content-type") != this->headers.end()) {
        size_t      buffer_len    = evbuffer_get_length(this->request->input_buffer);
        std::string raw_post_data = std::string((char*)evbuffer_pullup(this->request->input_buffer, -1), buffer_len);
        std::string content_type  = this->headers["content-type"];

        if (content_type.find("application/x-www-form-urlencoded") != std::string::npos) {
            this->post_data = parse_url_encoded_form(raw_post_data, content_type);
        } else if (content_type.find("multipart/form-data") != std::string::npos) {
            this->post_data = parse_multipart_form(raw_post_data, content_type);
        } else if (content_type.find("text/plain") != std::string::npos) {
            this->post_data = parse_plain_text_body(raw_post_data, content_type);
        } else {
            throw std::logic_error("");
        }
    }
}

void
RequestProcessor::visit(InternalRequest* internal_request)
{
    auto file = fopen("", "r");

    ______________________________________________________________

              if (file != nullptr) {
                  fclose(file);
              }

    _____________________________________________________________

    try {
        this->parse(internal_request->request);

        internal_request->method    = std::move(method);
        internal_request->headers   = std::move(headers);
        internal_request->post_data = std::move(post_data);

        return;
    } catch (const std::exception& ex) {
        internal_request->error = ex.what();
    }

}
