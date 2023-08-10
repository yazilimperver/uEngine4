cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME gl_painter)

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND CMAKE_PREFIX_PATH "D:/git_repos/Yazilimperver/uEngine4/code/src/ext/sdl2_libraries/glew-2.2.0")
find_package(GLEW REQUIRED)
find_package(FREEGLUT REQUIRED)
find_package(OpenGL REQUIRED)

# Baslik dosyalari
set(HEADER_FILES 
alias_mode.h
blend_equation.h
blend_factor.h
brush.h
brush_stippling_data.h
brush_style.h
color_ramp.h
geometry_type.h
gl_basic_painter.h
gl_include.h
gl_support.h
pen.h
pen_stippling_data.h
pen_style.h
simple_geometry.h
gl_font.h
gl_texture.h
vertex_data2d.h
gl_sprite_sheet.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
brush.cpp
color_ramp.cpp
gl_basic_painter.cpp
gl_support.cpp
pen.cpp
simple_geometry.cpp
gl_font.cpp
gl_texture.cpp
gl_sprite_sheet.cpp
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
target_include_directories(${LIB_NAME} PUBLIC ${DEVIL_DIR}/include  ${INFRA_INCLUDE_FOLDER} ${GLDIR_INCLUDE_FOLDER} ${GLM_DIR} ${GLEW_INCLUDE_DIRS} ${FREEGLUT_INCLUDE_DIRS} ${CEREAL_INCLUDE_DIRS} ${BASIC_ENGINE_INCLUDE_FOLDER} ${SDL_FONT_CACHE_INCLUDE_DIRS} )
target_include_directories(${LIB_NAME} PUBLIC ${FREETYPE_INCLUDE_DIRS} .)