cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME utility)

# Baslik dosyalari
set(HEADER_FILES
	parameter_set.h
	perf_utils.h
	property_item.h
	statistics.h
	unique_id_generator.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
    statistics.cpp
	property_item.cpp
	perf_utils.cpp
	parameter_set.cpp
	unique_id_generator.cpp	
 )

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Windows icin bir kac ek tanimlama
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()    

# Statik kutuphane olarak bu projeyi ekliyoruz
add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${LIB_NAME} PROPERTIES FOLDER Src/Infra)

# Kutuphaneleri baglayalim
target_link_libraries(${LIB_NAME} PUBLIC spdlog_header_only)
target_link_libraries(${LIB_NAME} PRIVATE fmt::fmt-header-only)

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER})
target_include_directories(${LIB_NAME} PUBLIC .)