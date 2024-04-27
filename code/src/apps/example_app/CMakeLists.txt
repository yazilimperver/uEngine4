cmake_minimum_required (VERSION 3.23)

# Isimlendirme
set(APP_NAME example_app)

find_package(SDL2 REQUIRED)

# Baslik dosyalari
set(HEADER_FILES
    "example_app.h"
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
    example_app.cpp
)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Konfigurasyon dosyasini da kopyalayalim
COPY_WIN_DLLS(${APP_NAME})

# kutuphaneleri baglayalim
#  ${CMAKE_DL_LIBS}'i kontrol edelim
target_link_libraries(${APP_NAME} infra nlohmann_json ${CMAKE_DL_LIBS}           
                                  SDL2::SDL2 SDL2::SDL2main)

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)