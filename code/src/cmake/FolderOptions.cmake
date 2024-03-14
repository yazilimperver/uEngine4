# Temel dizin animlamalarini yapalim
set(EXT_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/ext")

# Baslik dosyalarini ayri tutma kararimiz isiginda ilgili dizinleri ekleyelim
set(INFRA_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/infra")
set(BASIC_ENGINE_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/basic_engine")
set(GIS_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/gis")
set(GLDIR_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/gl")
set(FREETYPE_INCLUDE_DIRS "${EXT_INCLUDE_FOLDER}/freetype-master/include")

# CMake dosyalari icin nereye bakalim
set(SDLFONT_CACHE_DIR "${EXT_INCLUDE_FOLDER}/SDL_FontCache-master")
set(FREEGLUT_DIR "${EXT_INCLUDE_FOLDER}/freeglut-2.8.0")
set(CEREAL_DIR "${EXT_INCLUDE_FOLDER}/cereal-1.3.2")
set(THREAD_POOL_DIR "${EXT_INCLUDE_FOLDER}/thread-pool-master")
set(GLM_DIR "${EXT_INCLUDE_FOLDER}/glm-master")
set(TILESON_DIR "${EXT_INCLUDE_FOLDER}/tileson-master")
set(FMT_DIR "${EXT_INCLUDE_FOLDER}/fmt-8.1.1")
set(IMGUI_DIR "${EXT_INCLUDE_FOLDER}/imgui-master")
set(DEVIL_DIR "${EXT_INCLUDE_FOLDER}/devIL-1.8.0")
set(STB_DIR "${EXT_INCLUDE_FOLDER}/stb_image-2.28")
set(FREETYPE_DIR  "${EXT_INCLUDE_FOLDER}/freetype-master")
set(FREETYPE_LIBRARY "${EXT_INCLUDE_FOLDER}/freetype-master/build/Debug/freetyped.lib")