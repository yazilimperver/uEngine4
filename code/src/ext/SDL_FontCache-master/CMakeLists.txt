cmake_minimum_required(VERSION 3.1)
project(SDL_FontCache VERSION 0.10.0 LANGUAGES C)

find_path(sdl2_INCLUDE_DIR SDL.h PATHS ../SDL2-2.0.20/include)
find_library(sdl2_LIBRARY SDL2 PATHS ../SDL2-2.0.20/lib/x64)
find_library(sdl2main_LIBRARY SDL2main PATHS ../SDL2-2.0.20/lib/x64)
find_path(sdl2_ttf_INCLUDE_DIR SDL_ttf.h ../SDL2_ttf-2.20.0/include)
find_library(sdl2_ttf_LIBRARY SDL2_ttf ../SDL2_ttf-2.20.0/lib/x64)

if (NOT sdl2_INCLUDE_DIR)
    message(FATAL_ERROR "SDL2 include dir not found")
endif()
if (NOT sdl2_LIBRARY)
    message(FATAL_ERROR "SDL2 library dir not found")
endif()
if (NOT sdl2main_LIBRARY)
    message(FATAL_ERROR "SDL2main library dir not found")
endif()
if (NOT sdl2_ttf_INCLUDE_DIR)
    message(FATAL_ERROR "SDL2_TTF include dir not found")
endif()
if (NOT sdl2_ttf_LIBRARY)
    message(FATAL_ERROR "SDL2_TTF library dir not found")
endif()


add_library(FontCache
    SDL_FontCache.h
    SDL_FontCache.c
)
target_include_directories(FontCache PUBLIC ${sdl2_INCLUDE_DIR})
target_include_directories(FontCache PUBLIC .)
target_link_libraries(FontCache ${sdl2_LIBRARY})
target_link_libraries(FontCache ${sdl2main_LIBRARY})
target_include_directories(FontCache PUBLIC ${sdl2_ttf_INCLUDE_DIR})
target_link_libraries(FontCache ${sdl2_ttf_LIBRARY})

add_executable(FontCache-tests
	test/main.c
)
file(COPY test/utf8_sample.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY test/fonts/FreeSans.ttf DESTINATION ${CMAKE_BINARY_DIR}/fonts)
target_link_libraries(FontCache-tests FontCache)


