#ifndef FB_HTTP_SERVER_INTERFACES_HOST__
#define FB_HTTP_SERVER_INTERFACES_HOST__

#include "interfaces/guest.hpp"

#define HOST(serve)                  \
    template<typename Guest>         \
    inline void serve(Guest* guest)  \
    { guest->visit(this); }


#endif /* FB_HTTP_SERVER_INTERFACES_HOST__ */
