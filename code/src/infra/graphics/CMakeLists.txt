cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME graphics)

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(CEREAL REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
	color.h	
	color_serializer.h
	common.h
	envelope.h
	rectangle.h
	rectangle_serializer.h
	line.h
	point.h
	polygon.h
	polygon_triangulator.h
	intersection_result.h
	projection_result.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

set(SOURCE_FILES
	envelope.cpp
	line.cpp
	point.cpp
	polygon.cpp
	polygon_triangulator.cpp
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Statik kutuphane olarak bu projeyi ekliyoruz
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
else()
	add_library(${LIB_NAME} STATIC ${SOURCE_FILES})
endif()


# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER infra)
endif()

# Kutuphaneleri baglayalim
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_link_libraries(${LIB_NAME} spdlog_header_only)
endif()

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER} ${CEREAL_INCLUDE_DIRS} ${GLM_DIR})
target_include_directories(${LIB_NAME} PUBLIC .)