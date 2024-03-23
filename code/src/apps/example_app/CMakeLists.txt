cmake_minimum_required (VERSION 3.10)

# Isimlendirme
set(APP_NAME example_app)

find_package(SDL2 REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
    "example_app.h"
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
    example_app.cpp
)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# kutuphaneleri baglayalim
#  ${CMAKE_DL_LIBS}'i kontrol edelim
target_link_libraries(${APP_NAME} infra spdlog_header_only nlohmann_json ${CMAKE_DL_LIBS} )
target_link_libraries(${APP_NAME} SDL2::SDL2 SDL2::SDL2main)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${APP_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER})

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)

#if(WIN32)
#	add_custom_command(TARGET ${APP_NAME} POST_BUILD   # Adds a post-build event to ${APP_NAME}
#	    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
#	        "${SDL2_DLL_PATH}" 					       # <--this is in-file
#	         $<TARGET_FILE_DIR:${APP_NAME}>)           # <--this is out-file path
#endif()	         