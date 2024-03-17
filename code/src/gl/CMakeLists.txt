cmake_minimum_required (VERSION 3.23)

# Kaynak dosyalari icin hazirlanan ..._files.cmake dosyalarini bulmasi icin ekledik
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(FREETYPE REQUIRED)

# Isimlendirme
set(TARGET_NAME gl)

# CMake modul dosyaları
include(gl_core_loader_files)
include(gl_painter_files)
include(gl_texture_files)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("GL Loader Files" FILES ${GL_CORE_LOADER_FILES})
source_group("GL Painter Files" FILES ${GL_PAINTER_FILES})
source_group("GL Texture Files" FILES ${GL_TEXTURE_FILES})

# Kaynak ve olusturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${TARGET_NAME} STATIC ${GL_CORE_LOADER_FILES} ${GL_PAINTER_FILES} ${GL_TEXTURE_FILES})

# kutuphaneleri baglayalim
target_link_libraries(${TARGET_NAME} PRIVATE spdlog_header_only libglew_static glm::glm-header-only Freetype::Freetype)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${TARGET_NAME} PUBLIC ${STB_DIR} ${DEVIL_DIR}/include ${INFRA_INCLUDE_FOLDER} 
                                                 ${GLDIR_INCLUDE_FOLDER})