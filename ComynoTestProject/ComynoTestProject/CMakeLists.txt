# CMakeList.txt : CMake project for ComynoTestProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(cpprestsdk REQUIRED)
# Add source to this project's executable.
add_executable (ComynoTestProject "ComynoTestProject.cpp" "ComynoTestProject.h")
target_link_libraries(ComynoTestProject PRIVATE cpprestsdk::cpprest)
# TODO: Add tests and install targets if needed.
