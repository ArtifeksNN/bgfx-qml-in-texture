cmake_minimum_required(VERSION 3.10)

project(bgfx-qml-in-texture LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/bgfx/include
    ${CMAKE_SOURCE_DIR}/bx/include
    ${CMAKE_SOURCE_DIR}/bimg/include
    )

if (MINGW)
    link_directories(${CMAKE_SOURCE_DIR}/bgfx/.build/win64_mingw-gcc/bin)
endif(MINGW)
if (MSVC)
    link_directories(${CMAKE_SOURCE_DIR}/bgfx/.build/win64_vs2017/bin)
endif(MSVC)
if (UNIX)
    link_directories(${CMAKE_SOURCE_DIR}/bgfx/.build/linux64_gcc/bin)
endif(UNIX)

add_executable(bgfx-qml-in-texture
    main.cpp
    qml.qrc
    bgfx_item.h
    bgfx_item.cpp
    render_thread.h
    render_thread.cpp
    texture_node.h
    texture_node.cpp
    )

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

target_compile_definitions(bgfx-qml-in-texture
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
if (WIN32)
    target_link_libraries(bgfx-qml-in-texture
        PRIVATE Qt5::Core Qt5::Quick bgfxRelease bimgRelease bxRelease psapi)
endif(WIN32)
if (UNIX)
    target_link_libraries(bgfx-qml-in-texture
        PRIVATE Qt5::Core Qt5::Quick bgfxRelease bimgRelease bxRelease GL GLU X11 dl pthread rt)
endif(UNIX)



