set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Support both 32 and 64 bit builds
	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	  set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2main.lib")
	  set(SDL2_DLL_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.dll")
	else ()
	  set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2main.lib")
	  set(SDL2_DLL_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2.dll")
	endif ()
else()
	  set(SDL2_LIBRARIES "${CMAKE_SYSROOT}/usr/lib/x86_64-linux-gnu/libSDL2.a;${CMAKE_SYSROOT}/usr/lib/x86_64-linux-gnu/libSDL2main.a")
	  set(SDL2_DLL_PATH "${CMAKE_SYSROOT}//usr/lib/x86_64-linux-gnu/libSDL2.so")	
endif()

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)