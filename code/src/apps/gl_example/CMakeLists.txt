cmake_minimum_required (VERSION 3.10)

# Isimlendirme
set(APP_NAME gl_example)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
list(APPEND CMAKE_PREFIX_PATH "D:/git_repos/Yazilimperver/uEngine4/code/src/ext/sdl2_libraries/glew-2.2.0")
find_package(GLEW REQUIRED)
find_package(FREEGLUT REQUIRED)
find_package(CEREAL REQUIRED)
find_package(OpenGL REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
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
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DLIBSDL2_GFX_DLL_IMPORT)
endif()   

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Konfigurasyon dosyasini da kopyalayalim
add_custom_command(
    TARGET ${APP_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/sdl_application_configuration.json" "${CMAKE_CURRENT_BINARY_DIR}/"
    COMMENT "Copying sdl_application_configuration.json to build directory"
)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${APP_NAME} PRIVATE ${INFRA_INCLUDE_FOLDER} ${BASIC_ENGINE_INCLUDE_FOLDER} ${GLDIR_INCLUDE_FOLDER})
target_include_directories(${APP_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS}  ${CEREAL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${FREEGLUT_INCLUDE_DIRS})

# kutuphaneleri baglayalim
target_link_libraries(${APP_NAME} PRIVATE asset basic_engine gl_painter graphics sdl_application tick time utility nlohmann_json spdlog_header_only)
target_link_libraries(${APP_NAME} PRIVATE ${OPENGL_LIBRARIES} ${SDL_FONT_CACHE_LIBRARIES} ${CMAKE_DL_LIBS} ${FREEGLUT_LIBRARIES})
target_link_libraries(${APP_NAME} PRIVATE GLEW::glew)
target_link_libraries(${APP_NAME} PRIVATE SDL2::Main)
target_link_libraries(${APP_NAME} PRIVATE SDL2::Image )

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)

# Debug/release farki icin
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${APP_NAME}d )
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${APP_NAME} )