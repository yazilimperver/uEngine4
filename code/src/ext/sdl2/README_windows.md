Son SDL2 geliştirme paketi internetten indirilerek bu dizin altına açılır.
Paketler için https://github.com/libsdl-org/SDL/releases adresi üzerinden SDL2-devel-2.X.Y.Z-VC.zip isimli paket indirilerek dizin içerisine açılır. Dizin yapısı aşağıdaki gibi olmalıdır:

/ext/SDL2-2.X.Y/cmake
/ext/SDL2-2.X.Y/include
/ext/SDL2-2.X.Y/lib

ayrıca ilgili dizini tepe CMake betiği içerisinde de güncellemeniz gerekiyor:

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/SDL2-2.X.Y/cmake")