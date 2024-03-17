@echo off
setlocal

set SDL2_VC_LINK=https://github.com/libsdl-org/SDL/releases/download/release-2.24.0/SDL2-devel-2.24.0-VC.zip
set SDL2_SRC_LINK=https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.24.0.tar.gz

set SDL2Mixer_VC_LINK=https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.2/SDL2_mixer-devel-2.6.2-VC.zip
set SDL2Mixer_SRC_LINK=https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-2.6.2.tar.gz

set SDL2Image_VC_LINK=https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.2/SDL2_image-devel-2.6.2-VC.zip
set SDL2Image_SRC_LINK=https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.6.2.tar.gz

set SDL2TTF_VC_LINK=https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.1/SDL2_ttf-devel-2.20.1-VC.zip
set SDL2TTF_SRC_LINK=https://github.com/libsdl-org/SDL_ttf/archive/refs/tags/release-2.20.1.tar.gz

set SDL2Net_VC_LINK=https://github.com/libsdl-org/SDL_net/releases/download/release-2.2.0/SDL2_net-devel-2.2.0-VC.zip
set SDL2Net_SRC_LINK=https://github.com/libsdl-org/SDL_net/archive/refs/tags/release-2.2.0.tar.gz

set GLEW_VC_LINK=https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip
set GLEW_SRC_LINK=https://github.com/nigels-com/glew/archive/refs/tags/glew-2.2.0.tar.gz

echo Downloading and extracting SDL2 libraries
curl.exe -L %SDL2_VC_LINK% --output SDL2_VC.zip
tar -xf SDL2_VC.zip

echo Downloading and extracting SDL2 Mixer libraries
curl.exe -L %SDL2Mixer_VC_LINK% --output SDL2_Mixer_VC.zip
tar -xf SDL2_Mixer_VC.zip

echo Downloading and extracting SDL2 Image libraries
curl.exe -L %SDL2Image_VC_LINK% --output SDL2_Image_VC.zip
tar -xf SDL2_Image_VC.zip

echo Downloading and extracting SDL2 TTF libraries
curl.exe -L %SDL2TTF_VC_LINK% --output SDL2_TTF_VC.zip
tar -xf SDL2_TTF_VC.zip

echo Downloading and extracting SDL2 Net libraries
curl.exe -L %SDL2Net_VC_LINK% --output SDL2_Net_VC.zip
tar -xf SDL2_Net_VC.zip

echo Downloading and extracting GLEW libraries
curl.exe -L %GLEW_VC_LINK% --output GLEW_VC.zip
tar -xf GLEW_VC.zip

endlocal