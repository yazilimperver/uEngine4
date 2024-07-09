#!/bin/sh
echo Linux icin kontroller ve kurulumlar başlatılıyor

# Verilen komut var mi kontrol eder yok ise kurar
# Eger paket, komut ismindan farkli ise ikinci arguman olarak geciriliyor
CheckExistance() {
    if ! type "$1" > /dev/null; then
        # Bazen komutla paket ismi farklı olabiliyor. Onun için
        if [ $# -eq 2 ]; then
            echo "$2 kurulu değil, öncelikle onu kuralım"
            sudo apt install $2
        else
            echo "$1 kurulu değil, öncelikle onu kuralım"
            sudo apt install $1
        fi
    else
        echo "$1 kurulu, bu adım atlanıyor."
    fi
}

# Verilen SDL2 kutuphanesini indirir
# 1. arguman kutuphane ismi
# 2. arguman kutuphane dosya ismi
# 3. arguman kutuphane adresi
DownloadAndInstallSDL2Item(){
    echo "#################  $1 - START  ######################"

    if test -f $2.tar.gz; then
        echo $2.tar.gz dosyasi zaten var!
    else
        echo $2.tar.gz dosyasi yok. İndirilecek!
    fi
    
    wget $3
    tar -xvf $2.tar.gz
    rm $2.tar.gz*
    cd $2
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build --config Release --parallel
    sudo cmake --install build --config Release
    cd ..
    echo "#################  $1 - END  ######################"
}

DownloadAndInstallSDL2Libraries(){
    echo "#################  SDL - START  ######################"    
    cd code/ext
    mkdir sdl2
    cd sdl2

    DownloadAndInstallSDL2Item SDL2-Main SDL2-2.30.2 https://github.com/libsdl-org/SDL/releases/download/release-2.30.2/SDL2-2.30.2.tar.gz
    DownloadAndInstallSDL2Item SDL2-Image SDL2_image-2.8.2 https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.tar.gz
    DownloadAndInstallSDL2Item SDL2-TTF SDL2_ttf-2.22.0 https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.22.0.tar.gz

    echo "#################  SDL - END  ######################"    

    cd ../../..
}

# Gerekli araçlar var mı kontrol edelim
CheckExistance g++ build-essential
CheckExistance git
CheckExistance cmake
CheckExistance ninja ninja-build

# Kütüphane bağımlılıkları kurulacaktır
echo OpenGL bağımlılıkları kuruluyor
sudo apt-get install libxmu-dev libxi-dev libgl-dev -y

echo GLEW bağımlılıkları kuruluyor
sudo apt-get install libglew-dev -y

echo FreeType bağımlılıkları kuruluyor
sudo apt-get install libfreetype-dev -y

echo Lib Jpeg bağımlılıkları kuruluyor
sudo apt-get install libjpeg-dev -y

echo Curl bağımlılıkları kuruluyor
sudo apt install libcurl4-openssl-dev -y

echo DEVIL bağımlılıkları kuruluyor
cd code/ext
wget https://github.com/DentonW/DevIL/archive/refs/tags/v1.8.0.tar.gz
tar -xvf v1.8.0.tar.gz
rm v1.8.0.tar.gz
cd DevIL-1.8.0/DevIL
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --parallel
sudo cmake --install build --config Release
cd ../../../..

DownloadAndInstallSDL2Libraries

# cd code
# ./scripts/buildLinux.sh

echo Linux için kontroller ve kurulumlar tamamlandı