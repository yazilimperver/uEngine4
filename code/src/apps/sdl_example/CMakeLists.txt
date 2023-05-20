cmake_minimum_required (VERSION 3.10)

# Isimlendirme
set(APP_NAME sdl_example)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_TTF REQUIRED)
list(APPEND CMAKE_PREFIX_PATH "D:/git_repos/Yazilimperver/uEngine4/code/src/ext/sdl2_libraries/glew-2.2.0")
find_package(GLEW REQUIRED)
find_package(FREEGLUT REQUIRED)
find_package(CEREAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDLFONT_CACHE REQUIRED)


# Baslik dosyalari
set(HEADER_FILES
	primitive_sample.h
	sdl_gis_asset_sample.h
	sdl_input_sample.h
	sdl_painter_sample.h
	sdl_simple_shape.h
	sdl_sprite_sample.h
	sdl_sprite_sheet_sample.h
	sdl_texture_sample.h
	sdl_tile_map_sample.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
	main.cpp
	primitive_sample.cpp
	sdl_gis_asset_sample.cpp
	sdl_input_sample.cpp
	sdl_painter_sample.cpp
	sdl_simple_shape.cpp
	sdl_sprite_sample.cpp
	sdl_sprite_sheet_sample.cpp
	sdl_texture_sample.cpp
	sdl_tile_map_sample.cpp
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
target_link_libraries(${APP_NAME} asset basic_engine core_gis gis_asset painter sdl_application tick tile_map time sdl_asset utility sprite_sheet nlohmann_json spdlog_header_only)
target_link_libraries(${APP_NAME} ${OPENGL_LIBRARIES} ${SDL_FONT_CACHE_LIBRARIES} ${CMAKE_DL_LIBS})

target_link_libraries(${APP_NAME} GLEW::glew)
target_link_libraries(${APP_NAME} SDL2::Main)
target_link_libraries(${APP_NAME} SDL2::Image)

if(WIN32)
	target_link_libraries(${APP_NAME} SDL2::TTF)
else()
	target_link_libraries(${APP_NAME} SDL2::TTF freetype)
endif()

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${APP_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER} ${GIS_INCLUDE_FOLDER} ${BASIC_ENGINE_INCLUDE_FOLDER} ${SDL_FONT_CACHE_INCLUDE_DIRS} ${TILESON_DIR})
target_include_directories(${APP_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS}  ${CEREAL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${FREEGLUT_INCLUDE_DIRS})

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)

# Debug/release farki icin
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${APP_NAME}d )
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${APP_NAME} )
