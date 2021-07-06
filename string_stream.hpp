#ifndef FB_UTIL_STRING_STREAM_LIBRARY__
#define FB_UTIL_STRING_STREAM_LIBRARY__

#include <sstream>

namespace fb::utility {

class StringStream
{
private:
    std::stringstream stream;

public:
    StringStream();
    ~StringStream();

    template<typename Type>
    StringStream& operator<<(const Type& value)
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

}

#endif /* FB_UTIL_STRING_STREAM_LIBRARY__ */
