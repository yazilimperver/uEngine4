cmake_minimum_required (VERSION 3.23)

# CMake ile ilgili daha deyali log icin asagidaki satiri acmamiz gerekiyor
#set(CMAKE_FIND_DEBUG_MODE 1)

# https://cmake.org/cmake/help/latest/policy/CMP0135.html ilgili policy aktiflestirmek icin
cmake_policy(SET CMP0135 NEW)

# cmake konfigurasyon dizini
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})   

if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl2/SDL2-2.30.2/cmake")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl2/SDL2_image-2.8.2/cmake")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl2/SDL2_ttf-2.22.0/cmake")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype-master")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/glew-2.2.0")
endif()

# Ortak cmake betiklerini alalim
include(StandardOptions)    # Standard ayarlar
include(InsourceGuard)      # Source icerisinde buildi onleme

# Proje ismi, surum ve dil ayarlari
project(uengine4
    VERSION   1.0.0
    LANGUAGES C CXX
)

# Tepe Cmake dosyasinda C++ standardini eklyelim (projeler arasi uyumsuzlugun onune gecelim)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# OS Spesifik isler, proje tanimindan sonra olmali
include(TargetOSSetup)
include(CompilerOptions)
include(FolderOptions)
include(OpenGLOptions)
include(CommonFunctions)

# CCache'e yonelik ekleme
find_program(ccache_exe  ccache) 

if(ccache_exe )
    message("CCACHE is found")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)

    # CCache icin windows debug ve RelWithDebugInfo ayarlar
    if (MSVC)
        foreach(config DEBUG RELWITHDEBINFO)
            foreach(lang C CXX)
                set(flags_var "CMAKE_${lang}_FLAGS_${config}")
                string(REPLACE "/Zi" "/Z7" ${flags_var} "${${flags_var}}")
                set(${flags_var} "${${flags_var}}" PARENT_SCOPE)
            endforeach()
        endforeach()
    endif()
else(ccache_exe )
    message("CCACHE is NOT found")
endif(ccache_exe )

# Projeleri organize ederken dizinleri kullanmayi seciyioruz
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Dizinleri ortaklama icin boyle bir yontem izleyebiliriz
#foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
#    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
#    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
#    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
#    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/out )
#endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# If you only include this third party in PRIVATE source files, you do not need to install it
# when your main project gets installed.
set(JSON_Install OFF CACHE INTERNAL "")

if(BUILD_TESTING)
     # CMake üzerinden test kabiliyetlerini aktifleştirmek
     enable_testing()

     # GTesti sisteme kurmaya gerek yok 
     # Diger ayarlar icin https://github.com/google/googletest/blob/master/CMakeLists.txt goz atabilirsiniz
     set(INSTALL_GTEST OFF CACHE INTERNAL "")
     # Windows uzerinde calisma zamani hatalarini almamak icin bunu ekliyoruz.
     # Varsayılan olarak, yeni Visual Studio projeleri C çalışma zamanlarını dinamik olarak birbirine bağlar 
     # ancak GoogleTest bunları statik olarak bağlar. Bu durumda asağıdakine benzer hatalar alabilirsiniz:
     # "error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MT_StaticRelease' doesn't match value 'MD_DynamicRelease'"
     set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

if(TARGET_OS STREQUAL "Windows")
     add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# SPDLogu indirelim 
# Asagidaki kullanima gecilmesi durumunda 
# target'lardan `add_dependencies(${TARGET_NAME} spdlog)` kaldirilmali
# target'lara, target_link_libraries ifadelerine spdlog_header_only eklenmelidir
#include(FetchContent)
#FetchContent_Declare(
#     spdlog
#     GIT_REPOSITORY https://github.com/gabime/spdlog.git
#     GIT_TAG        v1.8.2)

# FetchContent_MakeAvailable(spdlog)

# Direk bagimlilik olarak kullanma
# Asagidaki kullanima gecilmesi durumunda 
# target'lar `add_dependencies(${TARGET_NAME} spdlog)` eklenmelidir
# target_link_libraries ifadelerinden spdlog_header_only cikarilmalidir
include(ExternalProject)
ExternalProject_Add(spdlog
    PREFIX spdlog
    SOURCE_DIR ${SPDLOG_DIR}
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_INSTALL_PREFIX=${SPDLOG_DIR}/install
    -DSPDLOG_BUILD_SHARED=OFF
)

message ("Staging dir is: ${STAGING_DIR}")

# Dis kütüphane alt dizinlerini ekleyelim
add_subdirectory ("ext")

# Statik kütüphane alt dizinlerini ekleyelim
add_subdirectory ("infra")
add_subdirectory ("gl")
add_subdirectory ("gis")
add_subdirectory ("basic_engine")

# Uygulama alt dizinlerini ekleyelim
add_subdirectory ("apps")

if(BUILD_TESTING)
     # Test projelerini ekleyelim
     add_subdirectory ("test")
endif()