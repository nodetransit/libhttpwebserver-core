#ifndef NT_HTTPWEBSERVER_RUNTIME_ERROR_FILE__
#define NT_HTTPWEBSERVER_RUNTIME_ERROR_FILE__

#include <string>
#include <memory>
#include <cstdio>
#include <cerrno>
#include <interfaces/error.hpp>

namespace nt { namespace error {

using nt::interfaces::Error;

class runtime :
      public Error<runtime>
{
};

}}

#endif /* NT_HTTPWEBSERVER_RUNTIME_ERROR_FILE__ */
