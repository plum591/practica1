cmake_minimum_required(VERSION 3.20.0)
project(practica1 VERSION 0.1.0 LANGUAGES C CXX)

set(wxWidgets_ROOT_DIR "D:/Libraries/wxWidgets")
set(wxWidgets_LIB_DIR "D:/Libraries/wxWidgets/lib/gcc1510_x64_dll")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})