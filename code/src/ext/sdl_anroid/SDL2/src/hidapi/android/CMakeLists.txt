set(PROJECT_NAME hidapi)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "../../../../libsdl/SDL/src/hidapi/android/hid.cpp"
)
source_group("" FILES ${no_group_source_files})

set(ALL_FILES
    ${no_group_source_files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE hidapi)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Android"
)
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$ENV{Sysroot}/usr/include;"
        "$ENV{StlIncludeDirectories};"
        "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$ENV{Sysroot}/usr/include;"
        "$ENV{StlIncludeDirectories};"
        "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$ENV{Sysroot}/usr/include;"
        "$ENV{StlIncludeDirectories};"
        "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/include"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$ENV{Sysroot}/usr/include;"
        "$ENV{StlIncludeDirectories};"
        "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM")
        target_compile_options(${PROJECT_NAME} PRIVATE
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM")
        target_link_options(${PROJECT_NAME} PRIVATE
            /DEBUG:FULL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM64")
        target_link_options(${PROJECT_NAME} PRIVATE
            /DEBUG:FULL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            /DEBUG:FULL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            /DEBUG:FULL
        )
    endif()
endif()

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$ENV{ToolchainPrebuiltPath}/lib/gcc/$ENV{ToolchainName}/$ENV{ToolchainFullVersionName}/$ENV{PlatformShortName};"
        "$ENV{StlLibraryPath};"
        "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "ARM64")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$ENV{ToolchainPrebuiltPath}/lib/gcc/$ENV{ToolchainName}/$ENV{ToolchainFullVersionName}/$ENV{PlatformShortName};"
        "$ENV{StlLibraryPath};"
        "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$ENV{ToolchainPrebuiltPath}/lib/gcc/$ENV{ToolchainName}/$ENV{ToolchainFullVersionName}/$ENV{PlatformShortName};"
        "$ENV{StlLibraryPath};"
        "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_link_directories(${PROJECT_NAME} PUBLIC
        "$ENV{ToolchainPrebuiltPath}/lib/gcc/$ENV{ToolchainName}/$ENV{ToolchainFullVersionName}/$ENV{PlatformShortName};"
        "$ENV{StlLibraryPath};"
        "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    )
endif()

