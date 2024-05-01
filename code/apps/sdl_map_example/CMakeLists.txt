cmake_minimum_required (VERSION 3.23)

# Isimlendirme
set(APP_NAME sdl_map_example)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(GLEW REQUIRED)

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

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Konfigurasyon dosyasini da kopyalayalim
COPY_WIN_DLLS(${APP_NAME})

# kutuphaneleri baglayalim
target_link_libraries(${APP_NAME} glm::glm-header-only infra gis nlohmann_json
								  ${OPENGL_LIBS}
								  SDL2::SDL2 SDL2_image::SDL2_image GLEW::glew)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_link_libraries(${APP_NAME} curl) 
else()
	target_link_libraries(${APP_NAME} ${CURL_DIR}/lib/libcurl.lib) 
endif()

target_include_directories(${APP_NAME} PUBLIC ${CURL_DIR}/include)

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)