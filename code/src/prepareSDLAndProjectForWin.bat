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

cd .\ext\sdl2_libraries

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

cd ..
cd ..

rmdir /s /q build
mkdir build
cd build

set ROOT_EXT_PATH="D:/GitRepository/Yazilimperver/uEngine4/code/src/ext/sdl2_libraries"
set SDL2_PATH="SDL2-2.24.0"
set SDL2_MIXER_PATH="SDL2_mixer-2.6.2"
set SDL2_IMAGE_PATH="SDL2_image-2.6.2"
set SDL2_TTF_PATH="SDL2_ttf-2.20.1"
set SDL2_NET_PATH="SDL2_net-2.2.0"
set GLEW_PATH="glew-2.2.0"

cmake -G "Visual Studio 17 2022" -A x64 ..  -DSDL2_PATH=%ROOT_EXT_PATH%/%SDL2_PATH%^
 -DSDL2_MIXER_PATH=%ROOT_EXT_PATH%/%SDL2_MIXER_PATH%^
 -DSDL2_IMAGE_PATH=%ROOT_EXT_PATH%/%SDL2_IMAGE_PATH%^
 -DSDL2_TTF_PATH=%ROOT_EXT_PATH%/%SDL2_TTF_PATH%^
 -DSDL2_NET_PATH=%ROOT_EXT_PATH%/%SDL2_NET_PATH%^
 -DGLEW_DIR=%ROOT_EXT_PATH%/%GLEW_PATH% -Wno-dev

cd ..

endlocal