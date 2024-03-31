cmake_minimum_required (VERSION 3.23)

# Isimlendirme
set(APP_NAME gl_example)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Asset dizinini ayarlayalim
set(EXAMPLE_ASSET_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../assets/gl_example_assets/)

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/configuration.h.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/configuration.h" )

# Baslik dosyalari
set(HEADER_FILES
    configuration.h
	gl_example.h
	gl_graphic_app.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
	main.cpp
	gl_example.cpp
	gl_graphic_app.cpp
)

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

set(CONFIG_FILES
	sdl_application_configuration.json
)

# Konfigurasyon dosya grubu (VS altindaki filtre gibi)
source_group("Config Files" FILES ${CONFIG_FILES})

# Windows icin bir kac ek tanimlama
if(TARGET_OS STREQUAL "Windows")
	add_definitions(-DLIBSDL2_GFX_DLL_IMPORT)
endif()   

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Konfigurasyon dosyasini da kopyalayalim
COPY_SDL_CONFIG_FILE(${APP_NAME})
COPY_WIN_DLLS(${APP_NAME})

# kutuphaneleri baglayalim
target_link_libraries(${APP_NAME} PRIVATE glm::glm-header-only infra gl nlohmann_json spdlog_header_only ${CMAKE_DL_LIBS} 
										Freetype::Freetype SDL2::SDL2 SDL2_image::SDL2_image GLEW::glew 
										${OPENGL_LIBS})

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)