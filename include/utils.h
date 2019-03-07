#ifndef WSQ2OTHER_UTILS_H
#define WSQ2OTHER_UTILS_H

#include <string>
#include <vector>

namespace wsq2jpeg {
  namespace utils {
    std::vector<std::string> get_files(const std::string&, std::vector<std::string>);
    bool check_file(const std::string&);
    bool check_dir(const std::string&);
    std::string get_name(const std::string&);
    std::string get_extension(const std::string&);
  }
}

#endif //WSQ2OTHER_UTILS_H
