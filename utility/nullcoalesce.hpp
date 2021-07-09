#ifndef FB_HTTP_SERVER_MACRO_NULL_COALESCE_HPP__
#define FB_HTTP_SERVER_MACRO_NULL_COALESCE_HPP__

namespace nt { namespace utility {

template<typename T>
inline T*
null_cx(T* a, T* b)
{
    return a == nullptr ?
        b :
        a;
}

}}

#endif /* FB_HTTP_SERVER_MACRO_NULL_COALESCE_HPP__ */
