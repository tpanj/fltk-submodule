cmake_minimum_required(VERSION 3.16)
project(MyFLTKProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add FLTK as a subdirectory
add_subdirectory(third_party/fltk)

# Add the source files
add_executable(MyFLTKProject src/main.cpp)

# Link FLTK to the project
target_link_libraries(MyFLTKProject PRIVATE fltk fltk_images fltk_jpeg fltk_png fltk_z)
