#include "internal_request.hpp"

using namespace nt::http;

InternalRequest::InternalRequest() :
      request(nullptr),
      error("")
{
}

InternalRequest::InternalRequest(evhttp_request* request) :
      request(request),
      error("")
{
}

InternalRequest::~InternalRequest()
{
}

/**
 * @brief
 * @see https://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
 * @return
 */
bool
InternalRequest::is_valid()
{
    return !method.empty() &&
           !uri.empty();
}

std::string
InternalRequest::get_error()
{
    return this->error;
}
