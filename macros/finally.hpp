#ifndef FB_HTTP_SERVER_MACRO_FINALLY_HPP__
#define FB_HTTP_SERVER_MACRO_FINALLY_HPP__

//finally.hpp

namespace fb
{
    class E {};
}

#define _using(x) \
    x;            \
    try

#define _try   \
    try

#define _leave \
    fb::E e;   \
    throw e;

#define _catch \
    catch

#define _throw \
    throw

#define _finally     \
    catch(fb::E& e)  \
    {                \
    }                \


#endif /* FB_HTTP_SERVER_MACRO_FINALLY_HPP__ */
