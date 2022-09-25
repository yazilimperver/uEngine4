cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME sdl_application)

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(CEREAL REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
	sdl_application.h
	sdl_gamepad_controller.h
	sdl_parameters.h
	sdl_parameters_serializer.h
	sdl_touch_service.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
   sdl_application.cpp
	sdl_application_common.cpp
	sdl_gamepad_controller.cpp
	sdl_touch_service.cpp
 )

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()    

unset(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER} ${GLEW_INCLUDE_DIRS} ${GLM_DIR} .)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SYSROOT}/usr/include ${CEREAL_INCLUDE_DIRS})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER infra)
endif()    

# kutuphaneleri baglayalim
target_link_libraries(${LIB_NAME} spdlog_header_only)
target_link_libraries(${LIB_NAME} SDL2::Main)