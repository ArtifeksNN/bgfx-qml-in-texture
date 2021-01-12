cmake_minimum_required(VERSION 3.14)

project(bgfx-qml-in-texture LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include_directories(
#    ${CMAKE_SOURCE_DIR}/bgfx/include
#    ${CMAKE_SOURCE_DIR}/bx/include
#    ${CMAKE_SOURCE_DIR}/bimg/include
#    )

#if (MINGW)
#    link_directories(${CMAKE_SOURCE_DIR}/bgfx/.build/win64_mingw-gcc/bin)
#endif(MINGW)
#if (MSVC)
#    link_directories(${CMAKE_SOURCE_DIR}/bgfx/.build/win64_vs2017/bin)
#endif(MSVC)
#if (UNIX)
#    link_directories(${CMAKE_SOURCE_DIR}/bgfx/.build/linux64_gcc/bin)
#endif(UNIX)

set(SOURCES
    main.cpp
    qml.qrc
    src/bgfx_item.h
    src/bgfx_item.cpp
    src/bgfx_item2.h
    src/bgfx_item2.cpp
    src/render_thread.h
    src/render_thread.cpp
    src/texture_node.h
    src/texture_node.cpp
    src/render_engine.h
    src/render_engine.cpp
)

add_executable(bgfx-qml-in-texture
    ${SOURCES}
)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Qml REQUIRED)
find_package(Qt5 COMPONENTS Quick REQUIRED)

target_link_libraries(bgfx-qml-in-texture PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::QuickPrivate
    bgfx
    bimg
    example-common
)

target_include_directories(bgfx-qml-in-texture
                            PUBLIC
                            ${CMAKE_SOURCE_DIR}/src
                            )

install(TARGETS bgfx-qml-in-texture
        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

add_subdirectory(3rdParty)
#target_compile_definitions(bgfx-qml-in-texture
#    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
#if (WIN32)
#    target_link_libraries(bgfx-qml-in-texture
#        PRIVATE Qt5::Core Qt5::Quick bgfxRelease bimgRelease bxRelease psapi)
#endif(WIN32)
#if (UNIX)
#    target_link_libraries(bgfx-qml-in-texture
#        PRIVATE Qt5::Core Qt5::Quick bgfxRelease bimgRelease bxRelease GL GLU X11 dl pthread rt)
#endif(UNIX)



