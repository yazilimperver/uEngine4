cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME raster_layer_sdl)

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDLFONT_CACHE REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(FMT REQUIRED)
find_package(CEREAL REQUIRED)

# Baslik dosyalari
set(SOURCE_FILES
	raster_sdl_layer.h
	raster_sdl_layer.cpp
    raster_sdl_renderer.cpp
    raster_sdl_renderer.h
    raster_sdl_layer_factory.h
    raster_sdl_layer_factory.cpp
)

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()    

unset(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${LIB_NAME} STATIC ${SOURCE_FILES})

# Bu bir C++ projesidiri direk soylemek gerekebiliyor
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${LIB_NAME} ${SDL_FONT_CACHE_LIBRARIES}  spdlog_header_only)
target_link_libraries(${LIB_NAME} SDL2::Main)
target_link_libraries(${LIB_NAME} SDL2::Image)
target_link_libraries(${LIB_NAME} SDL2::TTF)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} PUBLIC ${SDL_FONT_CACHE_INCLUDE_DIRS} ${GLDIR_INCLUDE_FOLDER} ${BASIC_ENGINE_INCLUDE_FOLDER} ${INFRA_INCLUDE_FOLDER} ${GIS_INCLUDE_FOLDER} ${GLM_DIR} .)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SYSROOT}/usr/include  ${FMT_INCLUDE_DIRS} ${CEREAL_INCLUDE_DIRS})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER gis)
endif()    