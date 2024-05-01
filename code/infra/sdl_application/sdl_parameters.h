#ifndef SDL_PARAMETERS
#define SDL_PARAMETERS

#include <cstdint>

//! Represent SDL parameters
struct SdlParameters {
    //! SDL number of Samples
    int32_t DepthSize;

    //! The major OpenGL context version
    int32_t MajorVersion;

    //! The minor OpenGL context version
    int32_t MinorVersion;

    //! Whether SDL window is resizable or not
    bool IsResizable;

    //! Whether logging is enabled or not
    bool IsDisplayEventLogs;

    /** @brief   True if gl is enabled, false if not */
    bool IsGLEnabled{ false };
};

#endif // !SDL_PARAMETERS