#include "httpstatus.hpp"

using namespace fb::http;

/* ************************************************** Information   */
const unsigned int status::code_continue            = 100;
const unsigned int status::code_switching_protocols = 101;
const unsigned int status::code_processing          = 102;
const unsigned int status::code_early_hints         = 103;

/* ************************************************** Success       */
const unsigned int status::code_ok                            = 200;
const unsigned int status::code_created                       = 201;
const unsigned int status::code_accepted                      = 202;
const unsigned int status::code_non_authoritative_information = 203;
const unsigned int status::code_no_content                    = 204;
const unsigned int status::code_reset_content                 = 205;
const unsigned int status::code_partial_content               = 206;
const unsigned int status::code_multi_status                  = 207;
const unsigned int status::code_already_reported              = 208;
const unsigned int status::code_im_used                       = 226;

/* ************************************************** Redirect      */
const unsigned int status::code_multiple_choices   = 300;
const unsigned int status::code_moved_permanently  = 301;
const unsigned int status::code_found              = 302;
const unsigned int status::code_see_other          = 303;
const unsigned int status::code_not_modified       = 304;
const unsigned int status::code_use_proxy          = 305;
const unsigned int status::code_temporary_redirect = 307;
const unsigned int status::code_permanent_redirect = 308;

/* ************************************************** Client Error  */
const unsigned int status::code_bad_request                     = 400;
const unsigned int status::code_unauthorized                    = 401;
const unsigned int status::code_payment_required                = 402;
const unsigned int status::code_forbidden                       = 403;
const unsigned int status::code_not_found                       = 404;
const unsigned int status::code_method_not_allowed              = 405;
const unsigned int status::code_not_acceptable                  = 406;
const unsigned int status::code_proxy_authentication_required   = 407;
const unsigned int status::code_request_timeout                 = 408;
const unsigned int status::code_conflict                        = 409;
const unsigned int status::code_gone                            = 410;
const unsigned int status::code_length_required                 = 411;
const unsigned int status::code_precondition_failed             = 412;
const unsigned int status::code_payload_too_large               = 413;
const unsigned int status::code_uri_too_long                    = 414;
const unsigned int status::code_unsupported_media_type          = 415;
const unsigned int status::code_range_not_satisfiable           = 416;
const unsigned int status::code_expectation_failed              = 417;
const unsigned int status::code_im_ateapot                      = 418;
const unsigned int status::code_unprocessable_entity            = 422;
const unsigned int status::code_locked                          = 423;
const unsigned int status::code_failed_dependency               = 424;
const unsigned int status::code_upgrade_required                = 426;
const unsigned int status::code_precondition_required           = 428;
const unsigned int status::code_too_many_requests               = 429;
const unsigned int status::code_request_header_fields_too_large = 431;
const unsigned int status::code_unavailable_for_legal_reasons   = 451;

/* ************************************************** Server Error  */
const unsigned int status::code_internal_server_error           = 500;
const unsigned int status::code_not_implemented                 = 501;
const unsigned int status::code_bad_gateway                     = 502;
const unsigned int status::code_service_unavailable             = 503;
const unsigned int status::code_gateway_timeout                 = 504;
const unsigned int status::code_http_version_not_supported      = 505;
const unsigned int status::code_variant_also_negotiates         = 506;
const unsigned int status::code_insufficient_storage            = 507;
const unsigned int status::code_loop_detected                   = 508;
const unsigned int status::code_not_extended                    = 510;
const unsigned int status::code_network_authentication_required = 511;

constexpr bool
status::is_informational(const unsigned int n)
{
    return (n >= 100 && n < 200);
}

constexpr bool
status::is_successful(const unsigned int n)
{
    return (n >= 200 && n < 300);
}

constexpr bool
status::is_redirection(const unsigned int n)
{
    return (n >= 300 && n < 400);
}

constexpr bool
status::is_client_error(const unsigned int n)
{
    return (n >= 400 && n < 500);
}

constexpr bool
status::is_server_error(const unsigned int n)
{
    return (n >= 500 && n < 600);
}

constexpr bool
status::is_error(const unsigned int n)
{
    return (n >= 400);
}

std::string
status::get_reason(const unsigned int n)
{
    switch (n) {

    /************************************************ Information   */
    case 100: return "Continue";
    case 101: return "Switching Protocols";
    case 102: return "Processing";
    case 103: return "Early Hints";

    /************************************************ Success       */
    case 200: return "OK";
    case 201: return "Created";
    case 202: return "Accepted";
    case 203: return "Non-Authoritative Information";
    case 204: return "No Content";
    case 205: return "Reset Content";
    case 206: return "Partial Content";
    case 207: return "Multi-Status";
    case 208: return "Already Reported";
    case 226: return "IM Used";

    /************************************************ Redirect      */
    case 300: return "Multiple Choices";
    case 301: return "Moved Permanently";
    case 302: return "Found";
    case 303: return "See Other";
    case 304: return "Not Modified";
    case 305: return "Use Proxy";
    case 307: return "Temporary Redirect";
    case 308: return "Permanent Redirect";

    /************************************************ Client Error  */
    case 400: return "Bad Request";
    case 401: return "Unauthorized";
    case 402: return "Payment Required";
    case 403: return "Forbidden";
    case 404: return "Not Found";
    case 405: return "Method Not Allowed";
    case 406: return "Not Acceptable";
    case 407: return "Proxy Authentication Required";
    case 408: return "Request Timeout";
    case 409: return "Conflict";
    case 410: return "Gone";
    case 411: return "Length Required";
    case 412: return "Precondition Failed";
    case 413: return "Payload Too Large";
    case 414: return "URI Too Long";
    case 415: return "Unsupported Media Type";
    case 416: return "Range Not Satisfiable";
    case 417: return "Expectation Failed";
    case 418: return "I'm a teapot";
    case 422: return "Unprocessable Entity";
    case 423: return "Locked";
    case 424: return "Failed Dependency";
    case 426: return "Upgrade Required";
    case 428: return "Precondition Required";
    case 429: return "Too Many Requests";
    case 431: return "Request Header Fields Too Large";
    case 451: return "Unavailable For Legal Reasons";

    /************************************************ Server Error  */
    case 500: return "Internal Server Error";
    case 501: return "Not Implemented";
    case 502: return "Bad Gateway";
    case 503: return "Service Unavailable";
    case 504: return "Gateway Time-out";
    case 505: return "HTTP Version Not Supported";
    case 506: return "Variant Also Negotiates";
    case 507: return "Insufficient Storage";
    case 508: return "Loop Detected";
    case 510: return "Not Extended";
    case 511: return "Network Authentication Required";

    default : return "";
    }
}

status::status()
{
}

