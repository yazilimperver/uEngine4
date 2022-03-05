# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("src")

# Uygulama alt dizinlerini ekleyelim
add_subdirectory ("example_app")

# Statik kütüphane alt dizinlerini ekleyelim
add_subdirectory ("infra")
