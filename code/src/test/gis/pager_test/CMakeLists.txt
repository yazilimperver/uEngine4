cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(APP_NAME pager_test)

# Kaynak kod dosyalari
set(SOURCE_FILES pager_test.cpp
    main.cpp)

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()    

# Test calistirilabilir dosyamiz
add_executable(${APP_NAME} ${SOURCE_FILES})


# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${APP_NAME} PROPERTIES FOLDER test/gis)
endif()    

# Kaynak dosyalarini nereden bulacagimizi belirleyelim
target_include_directories(${APP_NAME} PUBLIC ${INCLUDE_FOLDER})
target_include_directories(${APP_NAME} PUBLIC ${INCLUDE_FOLDER}/Utility)

target_link_libraries(${APP_NAME} gtest concurrency core_gis pager utility spdlog_header_only)
target_link_libraries(${APP_NAME} ${CMAKE_DL_LIBS})

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${APP_NAME} PUBLIC ${INFRA_INCLUDE_FOLDER})
target_include_directories(${APP_NAME} PUBLIC .)