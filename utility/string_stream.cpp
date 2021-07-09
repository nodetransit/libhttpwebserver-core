#include <stdexcept>
#include <sstream>
#include <string>

#include "string_stream.hpp"

using namespace nt::utility::string;

std::string
Stream::str() const
{
    return this->stream.str();
}

Stream::operator std::string() const
{
    return this->stream.str();
}

// std::string
// StringStream::operator>>(ConvertToString)
// {
//     return this->stream.str();
// }

