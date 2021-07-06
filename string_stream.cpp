#include <stdexcept>
#include <sstream>
#include <string>

#include "string_stream.hpp"

using namespace fb::utility;

StringStream::StringStream()
{}

StringStream::~StringStream()
{}

std::string
StringStream::str() const
{
    return this->stream.str();
}

StringStream::operator std::string() const
{
    return this->stream.str();
}

// std::string
// StringStream::operator>>(ConvertToString)
// {
//     return this->stream.str();
// }

