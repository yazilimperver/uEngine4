set(TARGET_OS
    ""
    CACHE STRING "Derleme icin hedef isletim sistemi: Windows, Linux")

if(TARGET_OS STREQUAL "")
  message(STATUS "TARGET_OS verilmedi. Otomatik olarak algilanacak...")

  if(WIN32)
    set(TARGET_OS "Windows")
    set(CMAKE_DEBUG_POSTFIX "_windows_debug")
    set(CMAKE_RELEASE_POSTFIX "_windows_release")
  elseif(UNIX AND NOT APPLE)
    set(TARGET_OS "Linux")
    set(CMAKE_DEBUG_POSTFIX "_linux_debug")
    set(CMAKE_RELEASE_POSTFIX "_linux_release")
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
  else()
    message(FATAL_ERROR "TARGET_OS otomatik tespit edilemedi")
  endif()

  message(STATUS "TARGET_OS otomatik olarak su sekilde ayarlandi: ${TARGET_OS}")
else()
  message(STATUS "TARGET_OS su sekilde verildi:  ${TARGET_OS}")
  if(TARGET_OS STREQUAL "Windows")
    set(CMAKE_DEBUG_POSTFIX "_windows_debug")
    set(CMAKE_RELEASE_POSTFIX "_windows_release")
  elseif(TARGET_OS STREQUAL "Linux")
    set(CMAKE_DEBUG_POSTFIX "_linux_debug")
    set(CMAKE_RELEASE_POSTFIX "_linux_release")
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
  else()
    message(FATAL_ERROR "TARGET_OS otomatik tespit edilemedi")
  endif()
endif()  