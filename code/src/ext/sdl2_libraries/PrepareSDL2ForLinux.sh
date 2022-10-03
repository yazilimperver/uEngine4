SDL2_SRC_LINK=https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.24.0.tar.gz
SDL2Mixer_SRC_LINK=https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-2.6.2.tar.gz
SDL2Image_SRC_LINK=https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.6.2.tar.gz
SDL2TTF_SRC_LINK=https://github.com/libsdl-org/SDL_ttf/archive/refs/tags/release-2.20.1.tar.gz
SDL2Net_SRC_LINK=https://github.com/libsdl-org/SDL_net/archive/refs/tags/release-2.2.0.tar.gz
GLEW_SRC_LINK=https://github.com/nigels-com/glew/archive/refs/tags/glew-2.2.0.tar.gz

GLEW_PATH=glew-glew-2.2.0
SDL2_PATH=SDL-release-2.24.0
SDL2_MIXER_PATH=SDL_mixer-release-2.6.2
SDL2_IMAGE_PATH=SDL_image-release-2.6.2
SDL2_TTF_PATH=SDL_ttf-release-2.20.1
SDL2_NET_PATH=SDL_net-release-2.2.0

echo Ucuncu parti bagimliliklar
sudo apt install cmake -y
sudo apt-get install build-essential libxmu-dev libxi-dev libgl-dev -y
sudo apt install ninja-build -y
sudo apt-get -y install libcurl4-openssl-dev
sudo apt install freeglut3-dev -y

echo Downloading and extracting GLEW libraries
wget $GLEW_SRC_LINK -O GLEW.tar.gz
tar -xf GLEW.tar.gz

echo GLEW icin python komutunu ayarlamaliyiz
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.10 10

cd glew-glew-2.2.0
cd auto
make
cd ..
make
sudo make install
make clean
cd ..

echo Downloading and extracting SDL2 libraries
wget $SDL2_SRC_LINK -O SDL2.tar.gz
tar -xf SDL2.tar.gz
cd $SDL2_PATH/
mkdir build
cd build
cmake ..
make
sudo make install
make clean
cd ..
cd ..

echo Downloading and extracting SDL2 Mixer libraries
wget $SDL2Mixer_SRC_LINK -O SDL2_Mixer.tar.gz
tar -xf SDL2_Mixer.tar.gz
cd $SDL2_MIXER_PATH
./configure
make
sudo make install
make clean
cd ..

echo Downloading and extracting SDL2 Image libraries
wget $SDL2Image_SRC_LINK -O SDL2_Image.tar.gz
tar -xf SDL2_Image.tar.gz
cd $SDL2_IMAGE_PATH
./configure
make
sudo make install
make clean
cd ..

echo Downloading and extracting SDL2 TTF libraries
wget $SDL2TTF_SRC_LINK -O SDL2_TTF.tar.gz
tar -xf SDL2_TTF.tar.gz
cd $SDL2_TTF_PATH
mkdir build
cd build
cmake ..
make
sudo make install
make clean
cd ..
cd ..

echo Downloading and extracting SDL2 Net libraries
wget $SDL2Net_SRC_LINK -O SDL2_NET.tar.gz
tar -xf SDL2_NET.tar.gz
cd $SDL2_NET_PATH
mkdir build
cd build
cmake ..
make
sudo make install
make clean
cd ..
cd ..
