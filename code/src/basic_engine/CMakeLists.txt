cmake_minimum_required (VERSION 3.23)

# Kaynak dosyalari icin hazirlanan ..._files.cmake dosyalarini bulmasi icin ekledik
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

# Isimlendirme
set(TARGET_NAME basic_engine)

# CMake modul dosyaları
include(basic_engine_files)
include(painter_files)
include(sprite_sheet_files)
include(tile_map_files)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Basic Engine Files" FILES ${BASIC_ENGINE_FILES})
source_group("Painter Files" FILES ${PAINTER_FILES})
source_group("Sprite Sheet Files" FILES ${SPRITE_SHEET_FILES})
source_group("Tile Map Files" FILES ${TILE_MAP_FILES})

# Kaynak ve olusturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${TARGET_NAME} STATIC ${BASIC_ENGINE_FILES} ${PAINTER_FILES}
                                  ${SPRITE_SHEET_FILES} ${TILE_MAP_FILES})

# kutuphaneleri baglayalim
target_link_libraries(${TARGET_NAME} PRIVATE SDL2_image::SDL2_image SDL2::SDL2 SDL2_ttf::SDL2_ttf 
                                             glm::glm-header-only spdlog_header_only)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${TARGET_NAME} PUBLIC ${STB_DIR} ${DEVIL_INCLUDE_DIR} ${INFRA_INCLUDE_FOLDER} 
                                                 ${GLDIR_INCLUDE_FOLDER} ${CEREAL_INCLUDE_DIR}
                                                 ${SDLFONT_CACHE_DIR} ${TILESON_DIR})