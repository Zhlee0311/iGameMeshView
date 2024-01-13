cmake_minimum_required(VERSION 3.19.2)
project(iGameView_Lite)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2 -pthread")
#添加宏定义
add_definitions(/D_USE_MATH_DEFINES)
add_compile_definitions(_HAS_STD_BYTE=0)

#编译器
# linux的GCC编译器
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "Compiler is GCC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O2 -pthread")
    #设置QT的目录
    set(QT_CMAKE_PATH "E:/Qt/5.14.2/mingw73_64/lib/cmake")

    #查找GLUT
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})

# Windows的MSVC编译器
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "Compiler is MSVC")
    #设置QT的目录
    set(QT_CMAKE_PATH "E:/Qt/5.14.2/msvc2017_64/lib/cmake")

    #查找GLUT
    SET(GLUT_INCLUDE_DIR extern/GLUT/include)
    SET(GLUT_LIBRARY extern/GLUT/lib/glut32.lib)
    include_directories(${GLUT_INCLUDE_DIR})
    include_directories(${GLUT_LIB_DIR})

    #以UTF-8格式进行编译
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# MacOS的AppleClang编译器
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    message(STATUS "Compiler is AppleClang")
    #设置QT的目录
    set(QT_CMAKE_PATH "/Users/lizhenghao/Qt5.14.2/5.14.2/clang_64/lib/cmake")

    #查找GLUT
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})

endif()

set(Qt5Core_DIR ${QT_CMAKE_PATH}/Qt5Core)
set(Qt5Gui_DIR ${QT_CMAKE_PATH}/Qt5Gui)
set(Qt5OpenGL_DIR ${QT_CMAKE_PATH}/Qt5OpenGL)
set(Qt5Widgets_DIR ${QT_CMAKE_PATH}/Qt5Widgets)
set(Qt5Charts_DIR ${QT_CMAKE_PATH}/Qt5Charts)

# 寻找系统中下载的三方库
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#path
SET(EIGEN_PATH "${PROJECT_SOURCE_DIR}/extern/")

#QT
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Charts REQUIRED)
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(DEPLOYQT_EXECUTABLE NAMES windeployqt macdeployqt HINTS "${_qt_bin_dir}")

set(QRC_SOURCE_FILES Turbine_Blade.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})
set(UI_SOURCE_FILES Turbine_Blade.ui)
qt5_wrap_ui(UI_FILES ${UI_SOURCE_FILES})

include_directories(${EIGEN_PATH})

include_directories(${PROJECT_SOURCE_DIR}/extern/)

file (GLOB GUI_FILE
        main.cpp
        iGameMeshView.*
        ModelDraw.*
        ViewOpenGL.*
        UI/*
        )

file (GLOB Mesh_FILE
        Volume_Algorithm/*
        Surface_Algorithm/*
        MeshKernel/*
        )

file (GLOB TOOLS_FILE
        Tools/*
        )

file (GLOB Ex_FILE
        extern/include/*
        )

# 必要3 项目中添加执行文件
add_executable(${PROJECT_NAME} ${SRCFILES}
        ${GUI_FILE}
        ${Mesh_FILE}
        ${QRC_FILES}
        ${UI_FILES}
        ${TOOLS_FILE}
        ${Ex_FILE}
        Surface_Algorithm/Surface_Fairing/Fairing.h
        Surface_Algorithm/Surface_Para/Para.h
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${DEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${PROJECT_NAME}>"
            --$<LOWER_CASE:$<CONFIG>> --qmldir ${CMAKE_SOURCE_DIR}
            )
endif()

source_group(GUI FILES ${GUI_FILE})
source_group(Mesh FILES ${Mesh_FILE})

target_include_directories(${PROJECT_NAME} PUBLIC
        extern/LibMeshFix/include/TMesh
        extern/LibMeshFix/include/Kernel
        )

target_compile_definitions(${PROJECT_NAME} PUBLIC -DIS64BITPLATFORM)

target_link_libraries(${PROJECT_NAME}
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::OpenGL
        Qt5::Charts
        )
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(${PROJECT_NAME}
            opengl32
            glu32
            ${QUAD_LIB_FILE}
            )
else()
    include_directories(${PROJECT_SOURCE_DIR})
    target_link_libraries(${PROJECT_NAME}
            ${GLUT_LIBRARY}
            ${OPENGL_LIBRARY}
            #-lgmp
            )
endif()

