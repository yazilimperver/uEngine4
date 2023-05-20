cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME gis_asset)

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(FMT REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
	gis_map_asset.h
	gis_map_loader.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
	gis_map_asset.cpp
	gis_map_loader.cpp
 )

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()    

unset(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

# Bu bir C++ projesidiri direk soylemek gerekebiliyor
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS} ${INFRA_INCLUDE_FOLDER} ${BASIC_ENGINE_INCLUDE_FOLDER} ${GIS_INCLUDE_FOLDER} ${GLM_DIR} ${SDL2_INCLUDE_DIRS} .)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SYSROOT}/usr/include  ${FMT_INCLUDE_DIRS})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER gis)
endif()    

# kutuphaneleri baglayalim
target_link_libraries(${LIB_NAME} spdlog_header_only)