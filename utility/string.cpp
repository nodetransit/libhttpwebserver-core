#include "string.hpp"

#include <macros/scope_guard.hpp>

#include <event.h>
#include <evhttp.h>

namespace nt { namespace utility { namespace string {

std::vector<std::string>
split(const std::string& s, const std::string& d)
{
    size_t start = 0;
    size_t len   = 0;

    std::vector<std::string> v;

    while (true) {
        len = s.find(d, start);

        if (len == std::string::npos) {
            v.push_back(s.substr(start));

            break;
        } else {
            v.push_back(s.substr(start, len - start));

            start = len + d.length();
        }
    }

    return v;
}

std::pair<std::string, std::string>
get_pair(const std::string& s, const std::string& d)
{
    if (s.empty() || s == d) {
        return {};
    }

    size_t index = s.find(d);

    bool has_value = index != std::string::npos;

    std::string val = has_value ?
                      s.substr(index + 1) :
                      std::string();

    std::string key = has_value ?
                      s.substr(0, index) :
                      s;

    return {key, val};
}

std::string
tolower(const std::string& s)
{
    std::string lower = s;

    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    return lower;
}

std::string
toupper(const std::string& s)
{
    std::string upper = s;

    std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) {
        return std::toupper(c);
    });

    return upper;
}

std::string
trim(const std::string& s, const std::string& c)
{
    std::string t = s;

    t = ltrim(t);
    t = rtrim(t);

    return t;
}

std::string
ltrim(const std::string& s, const std::string& c)
{
    std::string t = s;
    t.erase(t.begin(), std::find_if(t.begin(), t.end(), [&](unsigned char ch) {
        return c.find(ch) == std::string::npos;
    }));

    return t;
}

std::string
rtrim(const std::string& s, const std::string& c)
{
    std::string t = s;
    t.erase(std::find_if(t.rbegin(), t.rend(), [&](unsigned char ch) {
        return c.find(ch) == std::string::npos;
    }).base(), s.end());

    return t;
}

std::string
getline(std::string& s, const std::string& d)
{
    size_t start = 0;
    size_t len   = s.find(d, start);

    if (len != std::string::npos) {
        std::string line = s.substr(start, len);

        s.erase(start, len + d.length());

        return line;
    } else {
        return std::string();
    }
}

std::string
html_encode(const std::string& s)
{
    char* uri = evhttp_uriencode(s.c_str(), s.length(), true);

    ______________________________________________________________
              free(uri);
    _____________________________________________________________

    return std::string(uri);
}

std::string
html_decode(const std::string& s)
{
    size_t len;
    char* uri = evhttp_uridecode(s.c_str(), true, &len);

    ______________________________________________________________
           free(uri);
    _____________________________________________________________

    return std::string(uri);
}

std::string
from_cstr(const char* c, std::string d)
{
    return c != nullptr ?
           std::string(c) :
           d;
}

}}}
