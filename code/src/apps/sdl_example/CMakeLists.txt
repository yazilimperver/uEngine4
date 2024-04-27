cmake_minimum_required (VERSION 3.23)

# Isimlendirme
set(APP_NAME sdl_example)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(CEREAL REQUIRED)
find_package(SDLFONT_CACHE REQUIRED)

# Asset dizinini ayarlayalim
set(EXAMPLE_ASSET_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../assets/sdl_example_assets/)

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/configuration.h.in"
            "${CMAKE_CURRENT_SOURCE_DIR}/configuration.h" )

# Baslik dosyalari
set(HEADER_FILES
    configuration.h
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

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Konfigurasyon dosyasini da kopyalayalim
COPY_WIN_DLLS(${APP_NAME})

add_custom_command(
	TARGET ${APP_NAME} POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/SampleSpriteSheetConfig.json" "${CMAKE_CURRENT_BINARY_DIR}/"
	COMMENT "Copying SampleSpriteSheetConfig.json to build directory"
)

# kutuphaneleri baglayalim
target_link_libraries(${APP_NAME} infra gl gis basic_engine
								  ${OPENGL_LIBS} ${CMAKE_DL_LIBS} ${SDL_FONT_CACHE_LIBRARIES})

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${APP_NAME} PUBLIC ${SDL_FONT_CACHE_INCLUDE_DIRS} ${TILESON_DIR} ${CEREAL_INCLUDE_DIRS})

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)