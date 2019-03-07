#include <image.h>
#include <iostream>

void progress() {
  std::cout << ".";
  std::cout.flush();
}

int main(int argc, char** argv) {
  if (argc < 4) {
    std::cout<< "Invalid arguments. Run jpeg2wsq IN_PATH OUT_PATH BITRATE";
    return -1;
  }

  std::cout << "Running jpeg2wsq: ";

  wsq2jpeg::image::jpeg2wsq(argv[1], argv[2], atof(argv[3]), progress);

  std::cout << " OK" << std::endl;

  return 0;
}