project(qtzxing)
cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")

add_subdirectory(zxing)

set(BUILD_SHARED_LIBS false)

include_directories("./zxing/core/src")


set(QTZXING_PUBLIC_HEADERS
    qrvideowidget.h
    qrdecoder.h
)


set(QTZXING_PRIVATE_HEADERS
    qrquickitem.h
    qrvideosurface.h
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

set(CMAKE_AUTOMOC ON)

install(
  FILES ${QTZXING_PUBLIC_HEADERS}
  DESTINATION include/qtzxing
)

set(QTZXING_QT_MODULES Core Gui Widgets Multimedia)

find_package(Qt5Quick 5 QUIET)
if(Qt5Quick_FOUND)
    set(QTZXING_PLUGIN_SOURCES
        qtzxing_plugin.cpp
    )
    add_library(qtzxing_qml SHARED ${QTZXING_PLUGIN_SOURCES})
    target_link_libraries(qtzxing_qml qtzxing)
    install(FILES qmldir DESTINATION plugins/QtZXing)
    install(TARGETS qtzxing_qml DESTINATION plugins/QtZXing)
    set(QTZXING_SOURCES qrquickitem.cpp ${QTZXING_SOURCES})
    set(QTZXING_QT_MODULES Quick ${QTZXING_QT_MODULES})
endif()

add_library(qtzxing ${QTZXING_SOURCES})

target_link_libraries(qtzxing libzxing)

qt5_use_modules(qtzxing ${QTZXING_QT_MODULES})

install(TARGETS qtzxing DESTINATION lib)
