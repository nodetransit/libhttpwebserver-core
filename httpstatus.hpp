#ifndef FB_HTTP_STATUS_CODES_LIBRARY__
#define FB_HTTP_STATUS_CODES_LIBRARY__

#include <string>

namespace nt { namespace http {


class status
{
public:
    /************************************************ Information   */
    static const unsigned int code_continue;
    static const unsigned int code_switching_protocols;
    static const unsigned int code_processing;
    static const unsigned int code_early_hints;

    /************************************************ Success       */
    static const unsigned int code_ok;
    static const unsigned int code_created;
    static const unsigned int code_accepted;
    static const unsigned int code_non_authoritative_information;
    static const unsigned int code_no_content;
    static const unsigned int code_reset_content;
    static const unsigned int code_partial_content;
    static const unsigned int code_multi_status;
    static const unsigned int code_already_reported;
    static const unsigned int code_im_used;

    /************************************************ Redirect      */
    static const unsigned int code_multiple_choices;
    static const unsigned int code_moved_permanently;
    static const unsigned int code_found;
    static const unsigned int code_see_other;
    static const unsigned int code_not_modified;
    static const unsigned int code_use_proxy;
    static const unsigned int code_temporary_redirect;
    static const unsigned int code_permanent_redirect;

    /************************************************ Client Error  */
    static const unsigned int code_bad_request;
    static const unsigned int code_unauthorized;
    static const unsigned int code_payment_required;
    static const unsigned int code_forbidden;
    static const unsigned int code_not_found;
    static const unsigned int code_method_not_allowed;
    static const unsigned int code_not_acceptable;
    static const unsigned int code_proxy_authentication_required;
    static const unsigned int code_request_timeout;
    static const unsigned int code_conflict;
    static const unsigned int code_gone;
    static const unsigned int code_length_required;
    static const unsigned int code_precondition_failed;
    static const unsigned int code_payload_too_large;
    static const unsigned int code_uri_too_long;
    static const unsigned int code_unsupported_media_type;
    static const unsigned int code_range_not_satisfiable;
    static const unsigned int code_expectation_failed;
    static const unsigned int code_im_ateapot;
    static const unsigned int code_unprocessable_entity;
    static const unsigned int code_locked;
    static const unsigned int code_failed_dependency;
    static const unsigned int code_upgrade_required;
    static const unsigned int code_precondition_required;
    static const unsigned int code_too_many_requests;
    static const unsigned int code_request_header_fields_too_large;
    static const unsigned int code_unavailable_for_legal_reasons;

    /************************************************ Server Error  */
    static const unsigned int code_internal_server_error;
    static const unsigned int code_not_implemented;
    static const unsigned int code_bad_gateway;
    static const unsigned int code_service_unavailable;
    static const unsigned int code_gateway_timeout;
    static const unsigned int code_http_version_not_supported;
    static const unsigned int code_variant_also_negotiates;
    static const unsigned int code_insufficient_storage;
    static const unsigned int code_loop_detected;
    static const unsigned int code_not_extended;
    static const unsigned int code_network_authentication_required;

    constexpr static bool is_informational(const unsigned int);
    constexpr static bool is_successful(const unsigned int);
    constexpr static bool is_redirection(const unsigned int);
    constexpr static bool is_client_error(const unsigned int);
    constexpr static bool is_server_error(const unsigned int);
    constexpr static bool is_error(const unsigned int);

    static std::string get_reason(const unsigned int);

private:
    status();
};

}}

#endif /* FB_HTTP_STATUS_CODES_LIBRARY__ */
