::@echo off
:: Bu betik ile uEngine 4 icin ihtiyac duyulan ucuncu parti bagimliliklar kontrol edilecek/kurulacaktir
echo Windows için kontroller ve kurulumlar başlatılıyor& echo.

:: Tükrçe karakterler icin
chcp 65001 > NUL

:: oncelikle CMake kontrolü
call:CheckExistance cmake

:: ninja kontrolü
call:CheckExistance ninja

:: Ext'leri indirelim
:: Once glew. Glew icin ilave bir sey yapmaya gerek yok
call:DownloadAndExtractGlew

:: Sonra SDL2 kütüphaneleri
call:DownloadAndInstallSDL2Libraries

:: Sonra Freetype kütüphaneleri
call:DownloadAndInstallFreeType

:: Sonra Curl kütüphaneleri
call:DownloadAndInstallCurl

echo Windows için kontroller ve kurulumlar tamamlandı

:AfterSDL

:: Kurulumlar tamamlandı
EXIT /B 0

:: İlgili komut var mı kontrol eden fonksiyon
:CheckExistance

echo #################  %~1 - START ######################
where /q %~1.exe

if ERRORLEVEL 1 (
    echo %~1 kurulu değil. Lütfen kurunuz ve PATH ortam değiskenine eklendiğinden emin olunuz.
    exit /B
) ELSE (
    %~1 --version
    echo %~1 kurulu. Bir sonraki adıma geçelim!
)
echo ###################  %~1 -END ####################& echo.
EXIT /B 0

:: Glew kütüphanesi var mı yok ise indirelim
:DownloadAndExtractGlew

echo #################  GLEW - START  ######################& echo.

cd code\ext

if not exist glew.zip (
    curl.exe -L --ssl-revoke-best-effort https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip --output glew.zip
) else (
    echo glew.zip dosyası zaten var!
)
dir

tar -xvf glew.zip
del glew.zip

cd ../..

echo #################  GLEW - END  ######################& echo.
EXIT /B 0

:DownloadAndInstallSDL2Libraries
echo #################  SDL - START  ######################& echo.

cd code\ext\
mkdir sdl2
cd sdl2

:: Once ana SDL2 kutuphanesi
call:DownloadAndInstallSDL2Item SDL2-Main SDL2-devel-2.30.2-VC.zip https://github.com/libsdl-org/SDL/releases/download/release-2.30.2/SDL2-devel-2.30.2-VC.zip
call:DownloadAndInstallSDL2Item SDL2-Image SDL2_image-devel-2.8.2-VC.zip https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip
call:DownloadAndInstallSDL2Item SDL2-TTF SDL2_ttf-devel-2.22.0-VC.zip https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.22.0-VC.zip

cd ..\..\..

EXIT /B 0

:: Tek tek SDL kalemlerini indirmek icin 
:DownloadAndInstallSDL2Item
echo #################  %~1 - START  ######################& echo.
if not exist %~2 (
    curl.exe -L --ssl-revoke-best-effort %~3 --output %~2
) else (
    echo %~2 dosyası zaten var!
)
tar -xvf %~2
del %~2
echo #################  %~1 - END  ######################& echo.
EXIT /B 0

:: Freetype indirelim
:DownloadAndInstallFreeType
echo #################  FREETYPE - START  ######################& echo.
cd code\ext
if not exist ft2132.zip (
    curl.exe -L --ssl-revoke-best-effort https://github.com/ubawurinna/freetype-windows-binaries/archive/refs/tags/v2.13.2.zip --output ft2132.zip
) else (
    echo ft2132.zip dosyası zaten var!
)
tar -xvf ft2132.zip
cd freetype-windows-binaries-2.13.2
mkdir lib
copy ".\release static\vs2015-2022\win64\freetype.lib" .\lib\
cd ..
del ft2132.zip
cd ..\..
echo #################  FREETYPE - END  ######################& echo.
EXIT /B 0

:: CURL indirelim
:DownloadAndInstallCurl
echo #################  CURL - START  ######################& echo.
cd code\ext
if not exist curl-8.7.1.zip (
    curl.exe -L --ssl-revoke-best-effort https://curl.se/download/curl-8.7.1.zip --output curl-8.7.1.zip
) else (
    echo curl-8.7.1.zip dosyası zaten var!
)
tar -xvf curl-8.7.1.zip
cd curl-8.7.1
call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
cmake -B build_ninja -G "Ninja Multi-Config"
cmake --build build_ninja --config Release
cmake --build build_ninja --config Debug
pwd
dir .\build_ninja
dir .\build_ninja\lib
dir .\build_ninja\lib\Release
dir .\build_ninja\lib\Debug
mkdir lib
copy .\build_ninja\lib\Release\libcurl_imp.lib .\lib\libcurl.lib
copy .\build_ninja\lib\Debug\libcurl-d_imp.lib .\lib\libcurld.lib
cd ..
del curl-8.7.1.zip
cd ..\..
echo #################  CURL - END  ######################& echo.
EXIT /B 0