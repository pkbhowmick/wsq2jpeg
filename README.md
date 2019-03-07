wsq2jpeg - A Wavelet Scalar Quantization algorithm (WSQ) conversion library
===========================
Is a library to convert wsq images to jpeg format and vice versa. Allows individual or batch processing. Only supports images in grayscale. 
# Building form sources
## Compile NBIS
### Linux
```sh
 $ git clone https://github.com/rnhdev/wsq2jpeg
 $ git submodule update --init
 $ cd wsq2jpeg/third_party/nbis
 ./setup.sh . --without-X11 --64
 $ make config && make it
 $ cd ../..
 ```
 ## Compile and install
 ### Linux
 ```sh
 $ mkdir build 
 $ cd build
 $ cd cmake .. && make
 $ [sudo] make install
 ```
 ## Run examples
### WSQ to jpeg
```sh
 $ test_wsq ../test ../test 80
 ```
 ### jpeg to wsq 5:1
```sh
 $ test_jepg ../test ../test 2.25 
 ```
 
 ### jpeg to wsq 15:1
```sh
 $ test_jepg ../test ../test 0.75
 ```
