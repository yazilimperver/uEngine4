function(COPY_SDL_CONFIG_FILE ARG_APP_NAME)
    add_custom_command(
        TARGET ${ARG_APP_NAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/sdl_application_configuration.json" "${CMAKE_CURRENT_BINARY_DIR}/"
        COMMENT "Copying sdl_application_configuration.json to build directory"
    )
endfunction()     


function(COPY_WIN_DLLS ARG_APP_NAME)
if(TARGET_OS STREQUAL "Windows")
    file(GLOB DLLS_TO_COPY
    "${EXT_FOLDER}/dll/*.dll"
    )

    message("Copying dll files to build directory")
    foreach(DllToCopy IN LISTS DLLS_TO_COPY)
    add_custom_command(
                TARGET ${ARG_APP_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DllToCopy} "${CMAKE_CURRENT_BINARY_DIR}/"
                COMMENT "Copying dll: ${DllToCopy}")
    endforeach()
endif()    
endfunction()    