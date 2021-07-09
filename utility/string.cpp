#include "string.hpp"

#include <macros/scope_guard.hpp>

#include <dlib/logger.h>
#include <dlib/misc_api.h>
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

std::string
tolower(const std::string& s)
{
    return dlib::tolower(s);
}

std::string
trim(const std::string& s, const std::string& c)
{
    return dlib::trim(s, c);
}

std::string
ltrim(const std::string& s, const std::string& c)
{
    return dlib::ltrim(s, c);
}

std::string
rtrim(const std::string& s, const std::string& c)
{
    return dlib::rtrim(s, c);
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
