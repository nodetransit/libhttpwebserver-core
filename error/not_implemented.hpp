#ifndef NT_HTTPWEBSERVER_NOT_IMPLEMENTED_ERROR_FILE__
#define NT_HTTPWEBSERVER_NOT_IMPLEMENTED_ERROR_FILE__

#include <interfaces/error.hpp>

namespace nt { namespace error {

using nt::interfaces::Error;

class not_implemented :
      public Error<not_implemented>
{
};

}}

#endif /* NT_HTTPWEBSERVER_NOT_IMPLEMENTED_ERROR_FILE__ */
