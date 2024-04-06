# Alt projeler
cmake_minimum_required (VERSION 3.23)

# Kaynak dosyalari icin hazirlanan ..._files.cmake dosyalarini bulmasi icin ekledik
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Isimlendirme
set(TARGET_NAME infra)

# CMake modul dosyaları
include(application_base_files)
include(asset_files)
include(concurrency_files)
include(data_structures_files)
include(graphic_files)
include(sdl_application_files)
include(tick_files)
include(time_files)
include(utility_files)
include(imgui_files)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Application Base Files" FILES ${APP_BASE_FILES})
source_group("Asset Files" FILES ${ASSET_FILES})
source_group("SDL Asset Files" FILES ${SDL_ASSET_FILES})
source_group("Concurrency Files" FILES ${CONCURRENCY_FILES})
source_group("Data Structures Files" FILES ${DATASTRUCTURES_FILES})
source_group("Graphic Files" FILES ${GRAPHIC_FILES})
source_group("SDL Application Files" FILES ${SDL_APPLICATION_FILES})
source_group("Tick Files" FILES ${TICK_FILES})
source_group("Time Files" FILES ${TIME_FILES})
source_group("Utility Files" FILES ${UTILITY_FILES})
source_group("ImGUI Files" FILES ${IMGUI_FILES})

# Kaynak ve olusturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${TARGET_NAME} STATIC ${IMGUI_FILES} ${APP_BASE_FILES} ${ASSET_FILES} ${SDL_ASSET_FILES} ${CONCURRENCY_FILES}
                                  ${DATASTRUCTURES_FILES} ${GRAPHIC_FILES} ${SDL_APPLICATION_FILES}
                                  ${TICK_FILES} ${TIME_FILES} ${UTILITY_FILES} )


# kutuphaneleri baglayalim
target_link_libraries(${TARGET_NAME} PRIVATE spdlog::spdlog fmt::fmt-header-only GLEW::glew glm::glm-header-only)
target_link_libraries(${TARGET_NAME} PUBLIC  SDL2::SDL2 SDL2_image::SDL2_image)

# Baslik dosyalarinin yolunu ekleyelim (ImGUI backendleri icin dizin eklenmistir)
target_include_directories(${TARGET_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER} ${CEREAL_INCLUDE_DIR}
                                                  ${INFRA_INCLUDE_FOLDER}/im_gui  
                                                  ${GLDIR_INCLUDE_FOLDER} ${DEVIL_INCLUDE_DIR}
                                                  ${BASIC_ENGINE_INCLUDE_FOLDER})

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER _libs)