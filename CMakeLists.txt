cmake_minimum_required(VERSION 2.8)
project(wsq2jpeg)

set(CMAKE_CXX_STANDARD 11)
set(NBIS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party/nbis)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -std=c++11 -Wall  -Wno-reorder -Wno-deprecated-declarations")

link_directories(${NBIS_PATH}/exports/lib)

set(INCLUDE_PATH
    include
    ${NBIS_PATH}/exports/include)

set(LOCAL_SRC
    include/image.h
    src/image.cpp
    include/utils.h
    src/utils.cpp)

set(NBIS_OBJS
    ${NBIS_PATH}/imgtools/obj/src/lib/ihead/nullihdr.o
    ${NBIS_PATH}/imgtools/obj/src/lib/ihead/readihdr.o
    ${NBIS_PATH}/imgtools/obj/src/lib/ihead/writihdr.o
    ${NBIS_PATH}/imgtools/obj/src/lib/wsq/ppi.o
    ${NBIS_PATH}/imgtools/obj/src/lib/jpegl/tableio.o
    ${NBIS_PATH}/imgtools/obj/src/lib/image/imgdecod.o
    )

add_library(wsq2jpeg SHARED ${LOCAL_SRC} ${NBIS_OBJS})
add_executable(wsq2jpeg_test src/mainw.cpp)
add_executable(jpeg2wsq_test src/mainj.cpp)

target_include_directories(wsq2jpeg PRIVATE ${INCLUDE_PATH})
target_include_directories(wsq2jpeg_test PRIVATE include)
target_include_directories(jpeg2wsq_test PRIVATE include)

target_link_libraries(wsq2jpeg
    m
    liban2k.a
    libfet.a
    libihead.a
    libimage.a
    libioutil.a
    libjpegb.a
    libjpegl.a
    libopenjp2.a
    libpng.a
    libutil.a
    libwsq.a
    libz.a)

target_link_libraries(wsq2jpeg_test wsq2jpeg)
target_link_libraries(jpeg2wsq_test wsq2jpeg)

