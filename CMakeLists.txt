cmake_minimum_required(VERSION 3.9)
project(wsq2jpeg VERSION 1.0.1 DESCRIPTION "wsq to jpg converter and vice versa")
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(NBIS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party/nbis)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -std=c++11 -Wall  -Wno-reorder -Wno-deprecated-declarations")

link_directories(${NBIS_PATH}/exports/lib)

set(INCLUDE_PATH
    include
    ${NBIS_PATH}/exports/include)

set(LOCAL_SRC
    include/wsq2jpeg.h
    src/wsq2jpeg.cpp
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
set_target_properties(wsq2jpeg PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/wsq2jpeg.h)
target_include_directories(wsq2jpeg PRIVATE ${INCLUDE_PATH})
install(TARGETS wsq2jpeg
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(test_wsq src/test_wsq.cpp)
target_include_directories(test_wsq PRIVATE include)

add_executable(test_jpeg src/test_jpeg.cpp)
target_include_directories(test_jpeg PRIVATE include)

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

target_link_libraries(test_wsq wsq2jpeg)
target_link_libraries(test_jpeg wsq2jpeg)

