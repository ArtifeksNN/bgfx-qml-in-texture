cmake_minimum_required(VERSION 3.12)

project(bgfx-qml-in-texture LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(bgfx-qml-in-texture
    main.cpp
    qml.qrc
)

target_compile_definitions(bgfx-qml-in-texture
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(bgfx-qml-in-texture
  PRIVATE Qt5::Core Qt5::Quick)
