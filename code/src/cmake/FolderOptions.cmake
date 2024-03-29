# Temel dizin animlamalarini yapalim
set(EXT_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/ext")

# Baslik dosyalarini ayri tutma kararimiz isiginda ilgili dizinleri ekleyelim
set(INFRA_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/infra")
set(BASIC_ENGINE_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/basic_engine")
set(GIS_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/gis")
set(GLDIR_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/gl")

# CMake dosyalari icin nereye bakalim
set(SDLFONT_CACHE_DIR "${EXT_INCLUDE_FOLDER}/SDL_FontCache-master")
set(FREEGLUT_DIR "${EXT_INCLUDE_FOLDER}/freeglut-2.8.0")
set(CEREAL_DIR "${EXT_INCLUDE_FOLDER}/cereal-1.3.2")
set(CEREAL_INCLUDE_DIR "${CEREAL_DIR}/include")
set(THREAD_POOL_DIR "${EXT_INCLUDE_FOLDER}/thread-pool-master")
set(TILESON_DIR "${EXT_INCLUDE_FOLDER}/tileson-master")
set(IMGUI_DIR "${EXT_INCLUDE_FOLDER}/imgui-master")
set(DEVIL_DIR "${EXT_INCLUDE_FOLDER}/devIL-1.8.0")
set(DEVIL_INCLUDE_DIR "${EXT_INCLUDE_FOLDER}/devIL-1.8.0/include")
set(STB_DIR "${EXT_INCLUDE_FOLDER}/stb_image-2.28")