@echo off
setlocal

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