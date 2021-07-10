#ifndef NT_HTTPWEBSERVER_MEMORY_FILE__
#define NT_HTTPWEBSERVER_MEMORY_FILE__

#include <string>
#include <memory>
#include <cstdio>
#include <cerrno>
#include <interfaces/file.hpp>

#include "error.hpp"

namespace nt { namespace stream {


class MemoryFile :
      public nt::interfaces::File
{
private:
   FILE* file;
   char* buffer;


public:
    MemoryFile(const std::string&);
    ~MemoryFile() noexcept ;

};

}}

#endif /* NT_HTTPWEBSERVER_MEMORY_FILE__ */
