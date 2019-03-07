#ifndef WSQ2OTHER_IMAGE_H
#define WSQ2OTHER_IMAGE_H

#include <string>
#include <algorithm>
#include <functional>

namespace wsq2jpeg {
  namespace image {
    void wsq2jpeg(const std::string &in, const std::string &out, int out_qlt, std::function<void(void)> callback);
    void jpeg2wsq(const std::string &in, const std::string &out_folder, double out_bitrate,
                  std::function<void(void)> callback);
  }
}
#endif //WSQ2OTHER_IMAGE_H
