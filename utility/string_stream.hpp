#ifndef FB_UTIL_STRING_STREAM_LIBRARY__
#define FB_UTIL_STRING_STREAM_LIBRARY__

#include <sstream>

namespace nt { namespace utility { namespace string {

class Stream
{
private:
    std::stringstream stream;

public:
    Stream() = default;
    ~Stream() = default;

    template<typename Type>
    Stream& operator<<(const Type& value)
    {
        this->stream << value;

        return *this;
    }

    std::string str() const;
    operator std::string() const;

    // enum ConvertToString
    // {
    //     to_str
    // };
    //
    // std::string operator>>(ConvertToString);

private:
    // StringStream(const StringStream&);
    // StringStream& operator=(StringStream&);
};

}}}

#endif /* FB_UTIL_STRING_STREAM_LIBRARY__ */
