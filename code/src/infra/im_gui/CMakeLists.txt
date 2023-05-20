cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME im_gui)

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(CEREAL REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
	imconfig.h
	imgui.h
	imgui_internal.h
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
	backends/imgui_impl_opengl2.h
	backends/imgui_impl_opengl3.h
	backends/imgui_impl_osx.h
	backends/imgui_impl_sdl2.h
	backends/imgui_impl_sdlrenderer.h
	backends/imgui_impl_win32.h
	misc/cpp/imgui_stdlib.h)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

set(SOURCE_FILES
	imgui.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_tables.cpp
	imgui_widgets.cpp
	backends/imgui_impl_opengl2.cpp
	backends/imgui_impl_opengl3.cpp
	backends/imgui_impl_sdl2.cpp
	backends/imgui_impl_sdlrenderer.cpp
	misc/cpp/imgui_stdlib.cpp
	misc/fonts/binary_to_compressed_c.cpp
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Statik kutuphane olarak bu projeyi ekliyoruz
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
else()
	add_library(${LIB_NAME} STATIC ${SOURCE_FILES})
endif()


# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER infra)
endif()

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER} )
target_include_directories(${LIB_NAME} PUBLIC .)

target_link_libraries(${LIB_NAME} spdlog_header_only)
target_link_libraries(${LIB_NAME} SDL2::Main)