set(SDL_FONT_CACHE_ROOT_PATH ".."
    CACHE STRING "SDL Font Cache root path")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIB_POSTFIX_BUILD "D")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(LIB_POSTFIX_BUILD "")
endif()

if(TARGET_OS STREQUAL "Windows")
    set(LIB_PREFIX_OS "")
    if(SDL_FONT_CACHE_USE_S_LIBS STREQUAL "TRUE")
        set(LIB_POSTFIX_OS "s")    
    else()
        set(LIB_POSTFIX_OS "")    
    endif()  
    set(LIB_EXTENSION "lib")
    set(LIB_DIR "lib")
    set(LIB_POSTFIX_BUILD "")
elseif(TARGET_OS STREQUAL "Linux")
    set(LIB_PREFIX_OS "lib")
    set(LIB_POSTFIX_OS "")    
    set(LIB_EXTENSION "a")
    set(LIB_DIR "lib")
    set(LIB_POSTFIX_BUILD "")
endif()

set(SDL_FONT_CACHE_INCLUDE_PATH "${SDL_FONT_CACHE_ROOT_PATH}/include"
    CACHE STRING "SDL Font Cache include path")
    
set(SDL_FONT_CACHE_LIB "${SDL_FONT_CACHE_ROOT_PATH}/${LIB_DIR}/${LIB_PRETFIX_OS}FontCache${LIB_POSTFIX_OS}${LIB_POSTFIX_BUILD}.${LIB_EXTENSION}"
    CACHE STRING "SDL Font Cache lib")
    
add_library(sdl_font_cache STATIC IMPORTED)
set_property(TARGET sdl_font_cache PROPERTY IMPORTED_LOCATION ${SDL_FONT_CACHE_LIB})

# Varsa diger bagimliliklar
if(TARGET_OS STREQUAL "Linux")
    # find_package(Threads REQUIRED)
    # target_link_libraries(sdl_font_cache INTERFACE Threads::Threads)
    # target_link_libraries(sdl_font_cache INTERFACE dl)
    # target_link_libraries(sdl_font_cache INTERFACE rt)
endif()