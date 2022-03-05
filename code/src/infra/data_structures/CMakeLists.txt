# CMakeList.txt : CMake project for example_app, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(data_structures STATIC "stop_watch.cpp" "stop_watch.h")