cmake_minimum_required (VERSION 3.10)

# Isimlendirme
set(APP_NAME example_app)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Windows icin bir kac ek tanimlama
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()   

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# kutuphaneleri baglayalim
target_link_libraries(${APP_NAME} concurrency time)
target_link_libraries(${APP_NAME} nlohmann_json spdlog_header_only)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${APP_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER})

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER Src/Apps)

# Debug/release farki icin
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${APP_NAME}d )
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${APP_NAME} )