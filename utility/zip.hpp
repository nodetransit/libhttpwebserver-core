#ifndef FB_UTILITY_ZIP_LIBRARY__
#define FB_UTILITY_ZIP_LIBRARY__

#include <iostream>
#include <typeinfo>
#include <cstring>
#include <cstdarg>
#include <cstdlib>
#include <memory>
#include <vector>
#include <list>


/*
 * std::vector<int> a = {10,12,13};
 * std::vector<int> b = {21};
 * std::vector<int> c = {31,32,33,34};
 * int def = -1; // default value
 *
 * // if c++17
 * for (auto&& [x, y, z]: zip(def, a, b, c))
 *     std::cout << x << y << z << std::endl;
 *
 * // if c++14
 * for (auto&& zipped: zip(def, a, b, c))
 *     std::cout << zipped[0] << zipped[1] << zipped[2] << std::endl;
 *
 */



namespace nt { namespace utility { namespace collection {

template<size_t N, typename T>
class ZipIterator
{
private:
    std::vector<std::vector<T>>* items;

public:
    T* empty_value;
    unsigned int internal_counter;

    ZipIterator(auto i) :
          items(i)
    {
    }

    ZipIterator&
    operator++()
    {
        internal_counter++;
        return *this;
    }

    ZipIterator*
    operator++(int)
    {
        auto tmp = *this;

        ++(*this);

        return tmp;
    }

    friend bool
    operator!=(const ZipIterator& self, const ZipIterator& other)
    {
        return self.internal_counter != other.internal_counter;
    }

    friend bool
    operator==(const ZipIterator& self, const ZipIterator& other)
    {
        return self.internal_counter == other.internal_counter;
    }

    auto
    operator*() const
    {
        std::array < T, N > result;
        int i = 0;

        for (auto& item: *items) {
            if (item.size() <= internal_counter) {
                result[i] = *empty_value;
            } else {
                result[i] = item[internal_counter];
            }

            i++;
        }

        return result;
    }
};

template<size_t N, typename T, typename ... Ts>
class Zipper
{
private:
    T&& empty_value;
    std::vector<std::vector<T>> items;

    size_t       size;
    unsigned int max;

public:
    Zipper() = delete;

    Zipper(T&& value, Ts&& ... containers) :
          empty_value(std::forward<T>(value)),
          items({std::forward<Ts>(containers) ...}),
          size(N),
          max(0)
    {
        for (auto& item: items) {
            if (item.size() > max) {
                max = item.size();
            }
        }
    }

    auto
    begin()
    {
        ZipIterator<N, T> iterator(&items);

        iterator.internal_counter = 0;
        iterator.empty_value      = &empty_value;

        return iterator;
    }

    auto
    end()
    {
        ZipIterator<N, T> iterator(&items);

        iterator.internal_counter = max;
        iterator.empty_value      = &empty_value;

        return iterator;
    }
};

template<typename T, typename ... Ts>
auto
zip(T value, Ts&& ... items)
{
    return Zipper<sizeof ... (items), T, Ts ...>(std::forward<T>(value),
                                                 std::forward<Ts>(items) ...);
}

}}}

#endif /* FB_UTILITY_ZIP_LIBRARY__ */
