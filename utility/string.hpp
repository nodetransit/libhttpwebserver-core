#ifndef FB_UTILITY_STRING_LIBRARY__
#define FB_UTILITY_STRING_LIBRARY__

#include <sstream>
#include <string>
#include <vector>

namespace nt { namespace utility { namespace string {

std::vector<std::string> split(const std::string&, const std::string&);
std::string tolower(const std::string&);
std::string trim(const std::string&, const std::string& = " \r\n\t");
std::string ltrim(const std::string&, const std::string& = " \r\n\t");
std::string rtrim(const std::string&, const std::string& = " \r\n\t");
std::string getline(std::string&, const std::string& = "\n");

std::string html_encode(const std::string&);
std::string html_decode(const std::string&);

}}}

#endif /* FB_UTILITY_STRING_LIBRARY__ */
