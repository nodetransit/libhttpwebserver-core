#ifndef FB_UTILITY_STRING_LIBRARY__
#define FB_UTILITY_STRING_LIBRARY__

#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

namespace nt { namespace utility { namespace string {

std::vector<std::string> split(const std::string&, const std::string&);
std::pair<std::string, std::string> get_pair(const std::string&, const std::string&);
std::string tolower(const std::string&);
std::string toupper(const std::string&);
std::string trim(const std::string&, const std::string& = " 　\f\r\n\t\v");
std::string ltrim(const std::string&, const std::string& = " 　\f\r\n\t\v");
std::string rtrim(const std::string&, const std::string& = " 　\f\r\n\t\v");
std::string getline(std::string&, const std::string& = "\n");

std::string html_encode(const std::string&);
std::string html_decode(const std::string&);

std::string from_cstr(const char*, std::string = "");

}}}

#endif /* FB_UTILITY_STRING_LIBRARY__ */
