cmake_minimum_required (VERSION 3.10)

# Isimlendirme
set(APP_NAME sdl_map_example)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)
find_package(FREEGLUT REQUIRED)
find_package(CEREAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDLFONT_CACHE REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
	map_view.h
	sdlmap.h
	tile.h
	tile_collection.h
	tile_downloader.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
	map_view.cc
	sdlmap.cc
	tile.cc
	tile_collection.cc
	tile_downloader.cc
)

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Windows icin bir kac ek tanimlama
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()   

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# kutuphaneleri baglayalim
target_link_libraries(${APP_NAME} asset sdl_asset basic_engine core_gis painter nlohmann_json sdl_application time tick utility spdlog_header_only)
target_link_libraries(${APP_NAME} ${OPENGL_LIBRARIES} ${FMT_INCLUDE_DIRS} ${GLEW_LIBRARIES}  ${CMAKE_DL_LIBS})

target_link_libraries(${APP_NAME} SDL2::Main)
target_link_libraries(${APP_NAME} SDL2::Image)
target_link_libraries(${APP_NAME} SDL2::TTF)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${APP_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER} ${GIS_INCLUDE_FOLDER} ${SDL_FONT_CACHE_INCLUDE_DIRS} ${TILESON_DIR})
target_include_directories(${APP_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS}  ${CEREAL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${FREEGLUT_INCLUDE_DIRS})

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)

# Debug/release farki icin
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${APP_NAME}d )
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${APP_NAME} )       