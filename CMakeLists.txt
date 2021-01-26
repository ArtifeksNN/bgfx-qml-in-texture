cmake_minimum_required(VERSION 3.14)

project(bgfx-qml-in-texture LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    qml.qrc
    src/bgfx_item.h
    src/bgfx_item.cpp
    src/render_thread.h
    src/render_thread.cpp
    src/texture_node.h
    src/texture_node.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

find_package(Qt5 COMPONENTS Core)
find_package(Qt5 COMPONENTS Gui)
find_package(Qt5 COMPONENTS Qml)
find_package(Qt5 COMPONENTS Quick)

#target_link_libraries(bgfx-qml-in-texture PUBLIC
#    Qt::Core
#    Qt::Gui
#    Qt::Qml
#    Qt::Quick
#    Qt::QuickPrivate
#    bgfx
#    bimg
#    example-common
#)

target_include_directories(${PROJECT_NAME}
                            PUBLIC
                            ${CMAKE_SOURCE_DIR}/src
                            )

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

add_subdirectory(3rdParty)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
if (WIN32)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE Qt5::Core Qt5::Quick Qt5::Gui Qt5::Qml bgfx bimg bx psapi)
endif(WIN32)
if (UNIX)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE Qt5::Core Qt5::Quick Qt5::Gui Qt5::Qml bgfx bimg bx GL GLU X11 dl pthread rt)
endif(UNIX)



