#ifndef FB_HTTP_SERVER_MACRO_FINALLY_HPP__
#define FB_HTTP_SERVER_MACRO_FINALLY_HPP__

#include <memory>

#define ______scope_guard_concat_inner(a, b) a ## b
#define ______scope_guard_concat(a, b) ______scope_guard_concat_inner(a, b)

/**
 * @brief scope guard
 */
#define ______________________________________________________________ \
    auto ______scope_guard_concat(____nt__scope__guard__closure, __LINE__) =  \
    std::shared_ptr<char>((char*)[]()->void*{return nullptr;}(),[&](char*&)noexcept{
#define _____________________________________________________________ });

// #define _scope_guard(f, g) std::shared_ptr<char>((char*)[]()->void*{return nullptr;}(),[&](char*)noexcept{g});{f};
// #define sequence_block auto _scope_guard_concat(__scope__guard__, __LINE__) = _scope_guard
// #define code_block(...) __VA_ARGS__

#endif /* FB_HTTP_SERVER_MACRO_FINALLY_HPP__ */
