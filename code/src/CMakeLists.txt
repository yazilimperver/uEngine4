cmake_minimum_required(VERSION 3.10)

# Proje ismimiz. Bu VS kullanimi durumunda solutiona karsilik gelmekte
# Alt CMakeLists.txt icerisinden bu dizine `ApplicationMonitorTool_SOURCE_DIR` ile erisebiliriz
project(uEngine4)

# Otomatik surum ile ilgili konfigurasyon dosyasi olusturalim
set(PROJECT_NAME "uEngine4 Library")
set(CMAKE_PROJECT_VERSION_MAJOR 4)
set(CMAKE_PROJECT_VERSION_MINOR 0)
set(CMAKE_PROJECT_VERSION_PATCH 0)

# Temel dizin animlamalarini yapalim
set(EXT_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/ext")

# Baslik dosyalarini ayri tutma kararimiz isiginda ilgili dizinleri ekleyelim
set(INFRA_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/infra")
set(BASIC_ENGINE_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/basic_engine")
set(GIS_INCLUDE_FOLDER "${CMAKE_SOURCE_DIR}/gis")

# CMake dosyalari icin nereye bakalim
set(SDL2_DIR "${EXT_INCLUDE_FOLDER}/SDL2-2.0.20")
set(SDL2_TTF_DIR "${EXT_INCLUDE_FOLDER}/SDL2_ttf-2.20.0/cmake")
set(SDL2IMAGE_DIR "${EXT_INCLUDE_FOLDER}/SDL2_image-2.0.5")
set(SDLFONT_CACHE_DIR "${EXT_INCLUDE_FOLDER}/SDL_FontCache-master")
set(GLEW_DIR "${EXT_INCLUDE_FOLDER}/glew-2.1.0")
set(FREEGLUT_DIR "${EXT_INCLUDE_FOLDER}/freeglut-2.8.0")
set(CEREAL_DIR "${EXT_INCLUDE_FOLDER}/cereal-1.3.2")
set(THREAD_POOL_DIR "${EXT_INCLUDE_FOLDER}/thread-pool-master")
set(GLM_DIR "${EXT_INCLUDE_FOLDER}/glm-master")
set(TILESON_DIR "${EXT_INCLUDE_FOLDER}/tileson-master")
set(FMT_DIR "${EXT_INCLUDE_FOLDER}/fmt-8.1.1")

set(OpenGL_GL_PREFERENCE LEGACY)

# Projeleri organize ederken dizinleri kullanmayi seciyioruz
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Tepe Cmake dosyasinda C++ standardini eklyelim
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Debug derleme çıktıları sonuna d ekleyelim
set(CMAKE_DEBUG_POSTFIX d)

# Dizinleri ortaklama icin boyle bir yontem izleyebiliriz
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/out )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# CMake üzerinden test kabiliyetlerini aktifleştirmek
enable_testing()

# GTesti sisteme kurmaya gerek yok 
# Diger ayarlar icin https://github.com/google/googletest/blob/master/CMakeLists.txt goz atabilirsiniz
set(INSTALL_GTEST OFF CACHE INTERNAL "")

# If you only include this third party in PRIVATE source files, you do not need to install it
# when your main project gets installed.
set(JSON_Install OFF CACHE INTERNAL "")

# Windows uzerinde calisma zamani hatalarini almamak icin bunu ekliyoruz.
# Varsayılan olarak, yeni Visual Studio projeleri C çalışma zamanlarını dinamik olarak birbirine bağlar 
# ancak GoogleTest bunları statik olarak bağlar. Bu durumda asağıdakine benzer hatalar alabilirsiniz:
# "error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MT_StaticRelease' doesn't match value 'MD_DynamicRelease'"
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Uygulama alt dizinlerini ekleyelim
add_subdirectory ("apps")

# Statik kütüphane alt dizinlerini ekleyelim
add_subdirectory ("infra")
add_subdirectory ("gis")
add_subdirectory ("basic_engine")

# Dis kütüphane alt dizinlerini ekleyelim
add_subdirectory ("ext")

# Test projelerini ekleyelim
add_subdirectory ("test")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
     message(STATUS "Windows icin yazilim olusturma dosyalari hazirlaniyor.")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
     message(STATUS "Linux icin yazilim olusturma dosyalari hazirlaniyor.")    
endif()
