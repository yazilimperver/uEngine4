cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME core_gis)

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(FMT REQUIRED)
find_package(SDLFONT_CACHE REQUIRED)

# Baslik dosyalari
set(LAYER_FILES
	layer_status.h
	layer_renderer.h
	layer.h
	layer_management.h
	layer_service.h
	layer_status.h
	layer_renderer.h
	layer_controller.h
	layer_type.h
	layer_management.cpp
	layer_factory.h
	raster_layer.h
	raster_layer.cpp
	raster_layer_factory.h
	raster_layer_factory.cpp
	raster_controller.h
	raster_controller.cpp
	raster_sdl_renderer.h
	raster_sdl_renderer.cpp
)

set(CORE_FILES
	common.h
	geo_point.h
	gis_meta_data.h
	map_view.h
	slippy_map_util.h
	tile_tms.h
	geo_point.cpp
	main.cpp
	map_view.cpp
	slippy_map_util.cpp
	tile_tms.cpp
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Layer Management Files" FILES ${LAYER_FILES})

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Core Files" FILES ${CORE_FILES})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()    

unset(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${LIB_NAME} STATIC ${CORE_FILES} ${LAYER_FILES})

# Bu bir C++ projesidiri direk soylemek gerekebiliyor
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${LIB_NAME} ${SDL_FONT_CACHE_LIBRARIES}  spdlog_header_only)
target_link_libraries(${LIB_NAME} SDL2::Main)
target_link_libraries(${LIB_NAME} SDL2::Image)
target_link_libraries(${LIB_NAME} SDL2::TTF)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} PUBLIC ${BASIC_ENGINE_INCLUDE_FOLDER} ${INFRA_INCLUDE_FOLDER} ${GIS_INCLUDE_FOLDER} ${SDL_FONT_CACHE_INCLUDE_DIRS} ${GLM_DIR} .)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SYSROOT}/usr/include  ${FMT_INCLUDE_DIRS})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER gis)
endif()    