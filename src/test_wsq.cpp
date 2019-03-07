#include <wsq2jpeg.h>
#include <iostream>

static void progress() {
  std::cout << ".";
  std::cout.flush();
}

int main(int argc, char** argv) {
  if (argc < 4) {
    std::cout<< "Invalid arguments. Run wsq2jpeg IN_PATH OUT_PATH QLT";
    return -1;
  }

  std::cout << "Running wsq2jpeg: ";

  wsq2jpeg::image::wsq2jpeg(argv[1], argv[2], atoi(argv[3]), progress);

  std::cout << " OK" << std::endl;
  return 0;
}