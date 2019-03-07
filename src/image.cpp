#include "image.h"
#include "utils.h"
#include <vector>
#include <stdexcept>

#ifdef __cplusplus
extern "C" {
#endif
#include <imgdecod.h>
#include <img_io.h>
int debug =0;
#ifdef __cplusplus
} // extern "C"
#endif


namespace wsq2jpeg {
  namespace image {
    void wsq2jpeg(const std::string& in, const std::string& out_folder, int out_qlt,
                  std::function<void(void)> callback) {
      std::vector<std::string> file_list;

      if (utils::check_file(in) && utils::get_extension(in) == "wsq") {
        file_list.push_back(in);
      } else if (utils::check_dir(in)) {
        file_list = utils::get_files(in, std::vector<std::string>({"wsq"}));
      }

      if (file_list.size() == 0)
        throw std::invalid_argument(in + " is invalid or not contains WSQ files");

      if (out_qlt > 100 || out_qlt <= 0)
        out_qlt = 80;

      for (auto &file:file_list) {
        int img_type, dlen, w, h, d, ppi;
        unsigned char *data;
        // Read
        if (read_and_decode_grayscale_image((char *) file.c_str(), &img_type, &data, &dlen, &w, &h, &d, &ppi))
          throw std::invalid_argument("Error when reading image " + in);

        // Write
        int clen;
        unsigned char *cdata;
        auto comment_text = (char *) nullptr;

        std::string out = out_folder + "/" + utils::get_name(file) + ".jpg";
        if (jpegb_encode_mem(&cdata, &clen, out_qlt, data, w, h, d, ppi, comment_text)) {
          free(data);
          throw std::invalid_argument("Error encoding image " + out);
        }

        if (write_raw_from_memsize((char *) out.c_str(), cdata, clen)) {
          free(data);
          free(cdata);
          throw std::invalid_argument("Error encoding image " + out);
        }

        free(cdata);
        free(data);

        if(callback != nullptr)
          callback();
      }
    }

    void jpeg2wsq(const std::string &in, const std::string &out_folder, double out_bitrate,
                  std::function<void(void)> callback) {
      std::vector<std::string> file_list;

      if (utils::check_file(in) && utils::get_extension(in) == "jpg") {
        file_list.push_back(in);
      }
      else if (utils::check_dir(in)) {
        file_list = utils::get_files(in, std::vector<std::string>({"jpg"}));
      }

      if (file_list.size() == 0)
        throw std::invalid_argument(in + " is invalid or not contains jpeg files");

      if (out_bitrate <= 0)
        out_bitrate = 2.25;

      for (auto &file:file_list) {
        int img_type, dlen, w, h, d, ppi;
        unsigned char *data;
        // Read
        if (read_and_decode_grayscale_image((char *) file.c_str(), &img_type, &data, &dlen, &w, &h, &d, &ppi))
          throw std::invalid_argument("Error when reading image " + in);

        // Save image
        // Write
        int clen;
        unsigned char *cdata;
        auto comment_text = (char *) nullptr;

        std::string out = out_folder + "/" + utils::get_name(file) + ".wsq";
        if (wsq_encode_mem(&cdata, &clen, out_bitrate, data, w, h, 8, ppi, comment_text)) {
          free(data);
          throw std::invalid_argument("Error encoding image " + out);
        }

        if (write_raw_from_memsize((char *) out.c_str(), cdata, clen)) {
          free(data);
          free(cdata);
          throw std::invalid_argument("Error encoding image " + out);
        }

        free(cdata);
        free(data);

        if(callback != nullptr)
          callback();
      }
    }
  }
}