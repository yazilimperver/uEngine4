# Include sub-projects.
cmake_minimum_required (VERSION 3.23)

# Kaynak dosyalari icin hazirlanan ..._files.cmake dosyalarini bulmasi icin ekledik
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Isimlendirme
set(TARGET_NAME gis)

# CMake modul dosyaları
include(core_gis_files)
include(pager_files)
include(gis_asset_files)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Core GIS Files" FILES ${CORE_GIS_FILES})
source_group("Pager Files" FILES ${PAGER_FILES})
source_group("GIS Asset Files" FILES ${GIS_ASSET_FILES})

# Kaynak ve olusturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${TARGET_NAME} STATIC ${CORE_GIS_FILES} ${PAGER_FILES} ${GIS_ASSET_FILES})

# kutuphaneleri baglayalim
target_link_libraries(${TARGET_NAME} PRIVATE infra fmt-header-only)
target_link_libraries(${TARGET_NAME} PUBLIC glm::glm-header-only SDL2::SDL2 SDL2_image::SDL2_image)

add_dependencies(${TARGET_NAME} spdlog)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${TARGET_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER} ${GIS_INCLUDE_FOLDER}
                                                 ${CEREAL_INCLUDE_DIR} ${SPDLOG_DIR}/include )
                                                 
# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER uengine_libs)