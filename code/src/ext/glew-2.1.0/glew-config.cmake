set(GLEW_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(GLEW_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Release/x64/glew32.lib")
  set(GLEW_DLL_PATH "${CMAKE_CURRENT_LIST_DIR}/bin/Release/x64/glew32.dll")
else ()
  set(GLEW_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Release/Win32/glew32.lib")
  set(GLEW_DLL_PATH "${CMAKE_CURRENT_LIST_DIR}/bin/Release/Win32/glew32.dll")
endif ()

string(STRIP "${GLEW_LIBRARIES}" GLEW_LIBRARIES)