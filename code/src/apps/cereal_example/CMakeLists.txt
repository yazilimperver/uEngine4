cmake_minimum_required (VERSION 3.23)

# Isimlendirme
set(APP_NAME cereal_example)

# Olusturma dizinlerine de baslik dosyalari icin bakilmasina yonelik bir ayar
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Veri dosyalari
set(DATA_FILES
    "data.json"
)

# Dosya grubu (VS altindaki filtre gibi)
source_group("Resource Files" FILES ${DATA_FILES})

# Kaynak kod dosyalari
set(SOURCE_FILES
    main.cpp
)

# Kaynak dosya grubu (VS altindaki filtre gibi)
source_group("Source Files" FILES ${SOURCE_FILES})

# Calistirilabilir dosya olarak bu projeyi ekliyoruz
add_executable(${APP_NAME} ${DATA_FILES} ${SOURCE_FILES})

target_link_libraries(${APP_NAME} infra)

# Bu projeyi VS icerisinde ayri bir folderda tutalim
set_target_properties(${APP_NAME} PROPERTIES FOLDER apps)