cmake_minimum_required(VERSION 3.10)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDLFONT_CACHE REQUIRED)
find_package(CEREAL REQUIRED)

# Isimlendirme
set(LIB_NAME painter)

# Baslik dosyalari
set(HEADER_FILES
	brush.h
	common.h
	gfx_primitives.h
	gfx_primitives_font.h
	image_filter.h
	painter.h
	pen.h
	roto_zoom.h)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
	brush.cpp
	gfx_primitives.cpp
	image_filter.cpp
	painter.cpp
	pen.cpp
	roto_zoom.cpp
 )

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()    

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})


# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER basic_engine)
endif()    

# kutuphaneleri baglayalim
target_link_libraries(${LIB_NAME} spdlog_header_only)
target_link_libraries(${LIB_NAME} SDL2::Core)
target_link_libraries(${LIB_NAME} SDL2::TTF)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER} ${GLM_DIR} ${CEREAL_INCLUDE_DIRS} ${BASIC_ENGINE_INCLUDE_FOLDER} ${SDL_FONT_CACHE_INCLUDE_DIRS} )
target_include_directories(${LIB_NAME} PUBLIC .)