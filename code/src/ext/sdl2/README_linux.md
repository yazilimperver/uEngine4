Son SDL2 geliştirme paketi internetten indirilerek bu dizin altına açılır.
Paketler için https://github.com/libsdl-org/SDL/releases adresi üzerinden SDL2-2.X.Y.Z.tar.gz isimli paket indirilerek dizin içerisine açılır ve sonra aşağıdaki komutlar çalıştırılır:

cd /ext/SDL2-2.X.Y/
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release --parallel
sudo cmake --install . --config Release

komutlarının çalıştırılması yeterli.