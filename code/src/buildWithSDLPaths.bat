cd build

cmake -G "Visual Studio 17 2022" -A x64 ..  -DSDL2_PATH="D:/GitRepository/Yazilimperver/uEngine4/code/src/ext/sdl2_libraries/SDL2-2.24.0"^
 -DSDL2_MIXER_PATH="D:/GitRepository/Yazilimperver/uEngine4/code/src/ext/sdl2_libraries/SDL2_mixer-2.6.2"^
 -DSDL2_IMAGE_PATH="D:/GitRepository/Yazilimperver/uEngine4/code/src/ext/sdl2_libraries/SDL2_image-2.6.2"^
 -DSDL2_TTF_PATH="D:/GitRepository/Yazilimperver/uEngine4/code/src/ext/sdl2_libraries/SDL2_ttf-2.20.1"^
 -DGLEW_DIR="D:/GitRepository/Yazilimperver/uEngine4/code/src/ext/glew-2.2.0"

cd ..