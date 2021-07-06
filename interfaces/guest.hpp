#ifndef FB_HTTP_SERVER_INTERFACES_GUEST__
#define FB_HTTP_SERVER_INTERFACES_GUEST__

#include <typeinfo>

namespace fb::http::interfaces {

template<typename H>
class Guest
{
public:
    virtual void visit(H* host) = 0;
};

}

#endif /* FB_HTTP_SERVER_INTERFACES_GUEST__ */
