cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME graphics)

find_package(CEREAL REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
	color.h
	color_serializer.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Statik kutuphane olarak bu projeyi ekliyoruz
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_library(${LIB_NAME} INTERFACE ${HEADER_FILES})
else()
	add_library(${LIB_NAME} INTERFACE)
endif()


# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER Src/Infra)
endif()

# Kutuphaneleri baglayalim
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_link_libraries(${LIB_NAME} INTERFACE spdlog_header_only)
endif()

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} INTERFACE ${INFRA_INCLUDE_FOLDER} ${CEREAL_INCLUDE_DIRS})
target_include_directories(${LIB_NAME} INTERFACE .)