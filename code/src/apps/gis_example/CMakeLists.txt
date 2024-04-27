cmake_minimum_required (VERSION 3.23)

# Isimlendirme
set(APP_NAME gis_example)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(SDLFONT_CACHE REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
	gis_sample_app.h
	map_viewer_client_app.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
	gis_sample.cpp
	main.cpp
	map_viewer_client_app.cpp
)

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Konfigurasyon dosyasini da kopyalayalim
COPY_WIN_DLLS(${APP_NAME})

# kutuphaneleri baglayalim
target_link_libraries(${APP_NAME} glm::glm-header-only basic_engine infra gl gis nlohmann_json
								 ${OPENGL_LIBS} ${CMAKE_DL_LIBS}
								 Freetype::Freetype SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf GLEW::glew)								 

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)
