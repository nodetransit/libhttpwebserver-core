#ifndef FB_HTTP_SERVER_MACRO_NULL_COALESCE_HPP__
#define FB_HTTP_SERVER_MACRO_NULL_COALESCE_HPP__

#define NULLXX(a, b) \
    (a == nullptr ? b : a)

#endif /* FB_HTTP_SERVER_MACRO_NULL_COALESCE_HPP__ */
