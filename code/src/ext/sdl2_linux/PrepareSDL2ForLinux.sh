#!/bin/bash

# Ilgili kutuphane adresleri
SDL2_SRC_LINK=https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.24.0.tar.gz
SDL2Mixer_SRC_LINK=https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-2.6.2.tar.gz
SDL2Image_SRC_LINK=https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.6.2.tar.gz
SDL2TTF_SRC_LINK=https://github.com/libsdl-org/SDL_ttf/archive/refs/tags/release-2.20.1.tar.gz
SDL2Net_SRC_LINK=https://github.com/libsdl-org/SDL_net/archive/refs/tags/release-2.2.0.tar.gz
GLEW_SRC_LINK=https://github.com/nigels-com/glew/archive/refs/tags/glew-2.2.0.tar.gz

# Ilgili olusturma ve kurulum icin asagidaki degeri 1 yapalim
Enable_Dependency_Install=1
Enable_Glew_Install=1
Enable_Sdl2_Install=1
Enable_Sdl2_Mixer_Install=1
Enable_Sdl2_Image_Install=1
Enable_Sdl2_TTF_Install=1
Enable_Sdl2_Net_Install=1

# En son kontrol edilen GLEW ve SDL kutuphane isim/surumlari
GLEW_PATH=glew-glew-2.2.0
SDL2_PATH=SDL-release-2.24.0
SDL2_MIXER_PATH=SDL_mixer-release-2.6.2
SDL2_IMAGE_PATH=SDL_image-release-2.6.2
SDL2_TTF_PATH=SDL_ttf-release-2.20.1
SDL2_NET_PATH=SDL_net-release-2.2.0

echo "3. Parti Kurulum Aktif Mi: $Enable_Dependency_Install"
if [ $Enable_Dependency_Install = 1 ]
then
	echo "#################################################"
	echo "### 3rd Party Library Installation - START ######"
	echo "#################################################"

	sudo apt install cmake -y
	sudo apt-get install build-essential libxmu-dev libxi-dev libgl-dev -y
	sudo apt install ninja-build -y
	sudo apt-get install libgtest-dev
	sudo apt-get -y install libcurl4-openssl-dev
	sudo apt install freeglut3-dev -y
		
	echo "#################################################"
	echo "### 3rd Party Library Installation - END #######"
	echo "#################################################"
fi

echo "GLEW Kurulum Aktif Mi: $Enable_Glew_Install"
if [ $Enable_Glew_Install = 1 ]
then
	echo "#################################################"
	echo "### Performing GLEW Install Steps - START #######"
	echo "#################################################"

	echo Downloading and extracting GLEW libraries
	wget $GLEW_SRC_LINK -O GLEW.tar.gz
	tar -xf GLEW.tar.gz

	# Asagida verilen python dizini farkli olabilir lutfen kontrol ediniz!
	echo GLEW icin python komutunu ayarlamaliyiz
	sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.8 10

	cd glew-glew-2.2.0
	cd auto
	make
	cd ..
	make
	sudo make install
	make clean
	cd ..
		
	echo "#################################################"
	echo "### Performing GLEW Install Steps - END #######"
	echo "#################################################"
fi

echo "SDL2 Kurulum Aktif Mi: $Enable_Sdl2_Install"
if [ $Enable_Sdl2_Install = 1 ]
then
	echo "#################################################"
	echo "### Performing SDL2 Install Steps - START #######"
	
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
		
	echo "#################################################"
	echo "### Performing SDL2 Install Steps - END #########"
	echo "#################################################"
fi

echo "SDL2 Mikser Kurulum Aktif Mi: $Enable_Sdl2_Mixer_Install"
if [ $Enable_Sdl2_Mixer_Install = 1 ]
then
	echo "####################################################"
	echo "### Performing SDL2 Mixer Install Steps - START  ###"
	echo "####################################################"

	wget $SDL2Mixer_SRC_LINK -O SDL2_Mixer.tar.gz
	tar -xf SDL2_Mixer.tar.gz
	cd $SDL2_MIXER_PATH
	./configure
	make
	sudo make install
	make clean
	cd ..
		
	echo "#################################################"
	echo "### Performing SDL2 Mixer Install Steps - END ###"
	echo "#################################################"
fi

echo "SDL2 Imaj Kurulum Aktif Mi: $Enable_Sdl2_Image_Install"
if [ $Enable_Sdl2_Image_Install = 1 ]
then
	echo "####################################################"
	echo "### Performing SDL2 Image Install Steps - START  ###"
	echo "####################################################"

	wget $SDL2Image_SRC_LINK -O SDL2_Image.tar.gz
	tar -xf SDL2_Image.tar.gz
	cd $SDL2_IMAGE_PATH
	./configure
	make
	sudo make install
	make clean
	cd ..

	echo "#################################################"
	echo "### Performing SDL2 Image Install Steps - END ###"
	echo "#################################################"
fi	

echo "SDL2 TTF Kurulum Aktif Mi: $Enable_Sdl2_TTF_Install"
if [ $Enable_Sdl2_TTF_Install = 1 ]
then
	echo "####################################################"
	echo "### Performing SDL2 TTF Install Steps - START  ###"
	echo "####################################################"

	wget $SDL2TTF_SRC_LINK -O SDL2_TTF.tar.gz
	tar -xf SDL2_TTF.tar.gz
	# e49b603 - Bu SDL TTF surumu CMakeLists betigindeki problemin giderildigi dosyayi alalim (surum uyumsuzlugundan oturu)
	# c5478b1 - Ayrica kopyalama ile ilgili sikintinin da giderildi betik 
	cp SDL2_TTF_CMakeLists.txt SDL_ttf-release-2.20.1/CMakeLists.txt
	cd $SDL2_TTF_PATH
	mkdir build
	cd build
	cmake ..	
	make
	sudo make install
	make clean
	cd ..

	echo "#################################################"
	echo "### Performing SDL2 TTF Install Steps - END ###"
	echo "#################################################"
fi	

echo "SDL2 NET Kurulum Aktif Mi: $Enable_Sdl2_Net_Install"
if [ $Enable_Sdl2_Net_Install = 1 ]
then
	echo "####################################################"
	echo "### Performing SDL2 NET Install Steps - START  ###"
	echo "####################################################"

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

	echo "#################################################"
	echo "### Performing SDL2 NET Install Steps - END ###"
	echo "#################################################"
fi	
