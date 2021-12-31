#ifndef FB_UTILITY_ZIP_LIBRARY__
#define FB_UTILITY_ZIP_LIBRARY__

#include <iostream>
#include <cstring>
#include <cstdarg>
#include <cstdlib>

#define LINUX

#if defined(LOSER)
#elif defined(LINUX)
#endif

namespace nt { namespace utility { namespace collection {

template<typename T, typename... Ts>
std::vector<std::vector<T>>
zip(T s, std::vector<Ts>& ... items)
{
    auto list = {items...};

    int size = list.size();
    int max  = 0;

    for (auto& i: list) {
        if (i.size() > max) {
            max = i.size();
        }
    }

    std::vector<std::vector<T>> result;

    for (int j = 0; j < max; j++) {
        std::vector<T> p;

        for (auto& i: list) {
            if (i.size() <= j) {
                p.push_back(s);
            } else {
                p.push_back(i[j]);
            }
        }

        result.push_back(p);
    }

    return result;
}

}}}

#endif /* FB_UTILITY_ZIP_LIBRARY__ */
