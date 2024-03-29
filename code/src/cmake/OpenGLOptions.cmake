set(OpenGL_GL_PREFERENCE LEGACY)

option(USE_DEVIL "Use DEVIL Libraries" TRUE)

if(TARGET_OS STREQUAL "Windows")
    message("Windows OpenGL")
    set (OPENGL_LIBS opengl32.lib Glu32.lib)

    if(USE_DEVIL)
        list (APPEND OPENGL_LIBS ${DEVIL_DIR}/lib/DevIL.lib 
                                 ${DEVIL_DIR}/lib/ILU.lib 
                                 ${DEVIL_DIR}/lib/ILUT.lib)
    endif()
else()
    message("Linux OpenGL")
    set (OPENGL_LIBS GL GLU)

    if(USE_DEVIL)
        list (APPEND OPENGL_LIBS IL ILU ILUT)
    endif()
endif()