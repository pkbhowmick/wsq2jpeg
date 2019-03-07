#include "utils.h"

#include <dirent.h>
#include <memory>
#include <sys/stat.h>
#include <fstream>

namespace wsq2jpeg {
  namespace utils {
    struct stat info;

    std::vector<std::string> get_files(const std::string& folder, std::vector<std::string> admitted_extension) {
      std::vector<std::string> file_list;
      std::shared_ptr<DIR> directory_ptr(opendir(folder.c_str()), [](DIR* dir){ dir && closedir(dir); });
      struct dirent *dirent_ptr;
      while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr) {
        std::string name(dirent_ptr->d_name);
        auto ext = get_extension(name);

        for(auto &filter:admitted_extension) {
          if(ext==filter) {
            file_list.push_back(folder + "/" + name);
            break;
          }
        }
      }

      return file_list;
    }
    bool check_file(const std::string& file) {
      return stat(file.c_str(),&info) == 0 && info.st_mode & S_IFREG;
    }
    bool check_dir(const std::string& folder) {
      return stat(folder.c_str(),&info) == 0 && info.st_mode & S_IFDIR;
    }
    std::string get_name(const std::string& file) {
      int start = file.rfind('/')+1;
      return file.substr(start, file.rfind('.') - start);
    }
    std::string get_extension(const std::string& file) {
      return file.substr(file.rfind('.') + 1);
    }
  }
}