cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME gl_texture)

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND CMAKE_PREFIX_PATH "D:/git_repos/Yazilimperver/ugmap/code/src/ext/sdl2_libraries/glew-2.2.0")
find_package(GLEW REQUIRED)
find_package(FREEGLUT REQUIRED)
find_package(OpenGL REQUIRED)

# Baslik dosyalari
set(HEADER_FILES 
    pixel_format.h
    pixel_type.h
    texture_asset.h
    texture_bpp.h
    texture_common.h
    texture_info.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
    texture_asset.cpp
)

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()    

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})


# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER gl)
endif()    

# kutuphaneleri baglayalim
target_link_libraries(${LIB_NAME} spdlog_header_only)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER} ${GLM_DIR} ${GLEW_INCLUDE_DIRS} ${FREEGLUT_INCLUDE_DIRS} ${CEREAL_INCLUDE_DIRS} ${BASIC_ENGINE_INCLUDE_FOLDER} ${SDL_FONT_CACHE_INCLUDE_DIRS} )
target_include_directories(${LIB_NAME} PUBLIC .)