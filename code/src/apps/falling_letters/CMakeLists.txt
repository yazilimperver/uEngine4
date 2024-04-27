cmake_minimum_required (VERSION 3.23)

# Isimlendirme
set(APP_NAME falling_letters)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDLFONT_CACHE REQUIRED)

# Asset dizinini ayarlayalim
set(EXAMPLE_ASSET_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../assets/falling_letters_assets/)

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/configuration.h.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/configuration.h" )

# Baslik dosyalari
set(HEADER_FILES
    configuration.h
	falling_letters_app.h
	falling_letters_graphics_app.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
	main.cpp
	falling_letters_app.cpp
	falling_letters_graphics_app.cpp
)

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Konfigurasyon dosyasini da kopyalayalim
COPY_SDL_CONFIG_FILE(${APP_NAME})
COPY_WIN_DLLS(${APP_NAME})

# kutuphaneleri baglayalim
target_link_libraries(${APP_NAME} infra gl basic_engine
 								  ${CMAKE_DL_LIBS} ${OPENGL_LIBS}  ${SDL_FONT_CACHE_LIBRARIES}
)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${APP_NAME} PUBLIC ${CEREAL_INCLUDE_DIRS} ${SDL_FONT_CACHE_INCLUDE_DIRS})

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)
