project(qtzxing)
cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")

add_subdirectory(zxing)

set(BUILD_SHARED_LIBS false)

include_directories("./zxing/core/src")


set(QTZXING_PUBLIC_HEADERS
    qrvideosurface.h
    qrquickitem.h
    qrvideowidget.h
    qrdecoder.h
)


set(QTZXING_PRIVATE_HEADERS
    zxingimagesource.h
)

find_package(Qt5Widgets 5)
find_package(Qt5Core 5)
find_package(Qt5Gui 5)
find_package(Qt5Multimedia 5)

set(QTZXING_SOURCES
    qrvideosurface.cpp
    zxingimagesource.cpp
    qrvideowidget.cpp
    qrdecoder.cpp
)

find_package(Qt5Quick 5 QUIET)

set(QTZXING_QT_MODULES Core Gui Widgets Multimedia)

if (Qt5Quick_FOUND)
    set(QTZXING_SOURCES qrquickitem.cpp ${QTZXING_SOURCES})
    set(QTZXING_QT_MODULES Quick ${QTZXING_QT_MODULES})
endif()

add_library(qtzxing SHARED ${QTZXING_SOURCES})

target_link_libraries(qtzxing libzxing)

install(
  FILES ${QTZXING_HEADERS}
  DESTINATION include/qtzxing
)

install (TARGETS qtzxing DESTINATION lib)

qt5_use_modules(qtzxing ${QTZXING_QT_MODULES})
