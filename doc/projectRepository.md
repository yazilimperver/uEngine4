# uEngine4 Kütüphanesi Proje Dizin yapısı

- /uEngine4 : Ana dizin
- /uEngine4/assets : Örnek ve diğer yerlerde kullanılacak olan verilerin bulunduğu dizin
- /uEngine4/doc : Proje ile ilgili dokümanlar
- /uEngine4/code : Kütüphane ile ilgili kaynak kod ve ilintili kalemler. Şimdi, /uEngine4/code altındaki dizinlere bir bakalım.
	* binary: Kütüphane ve örneklerin çıktılarının toplandığı dizin
	* project: Kütüphane ve örneklerin Visual Studio 2022 dosyalarının tutulduğu dizinlerdir. 
	* project/vs_property_sheets: VS2022 hazır proje ayar dosyalarının tutulduğu dizindir.
	* src : Kütüphane ile ilgili kaynak kodların bulunduğu dizinler
	* src/infra: Temel kabiliyetlere ilişkin kaynak kodların bulunduğu dizin.
	* src/basic_engine: 2B SDL tabanlı oyun motoruna ilişkin kütüphaneleri içeren dizindir.
	* src/gis: CBS kabiliyetlerinin bulunacağı dizindir.
	* src/apps: uEngine4 kullanan örnek uygulamalarına ilişkin kaynak kodların bulunduğu dizin.	
	* src/test: Birim testlerin bulunacağı dizindir.
	* src/ext: Kullanılan 3. parti kütüphanelerin bulunduğu dizindir.
	
.
└── uEngine4/
    ├── assets
    ├── doc
    └── code/
        ├── binary
        ├── project/
        │   ├── vs_property_sheet
        │   └── vs2022
        └── src/
            ├── apps/
            │   ├── cereal_example
            │   ├── example_app
            │   ├── gis_example
            │   ├── sdl_example
            │   └── sdl_map_example     
            ├── basic_engine/
            │   ├── asset
            │   ├── basic_engine
            │   ├── painter
            │   ├── sdl_asset
            │   ├── sprite_sheet
            │   └── tile_map
            ├── ext/
            │   ├── cereal-1.3.2
            │   ├── fmt-8.1.1
            │   ├── freeglut-2.8.0
            │   ├── glew-2.2.0
            │   ├── glm-master
            │   ├── googletest-master
            │   ├── json-develop
            │   ├── sdl2_libraries
            │   ├── sdl_anroid
            │   ├── SDL_FontCache-master
            │   ├── shared_queues
            │   ├── spdlog-1.x
            │   ├── thread-pool-master
            │   └── tileson-master
            ├── gis/
            │   ├── core_gis
            │   └── pager
            ├── infra/
            │   ├── application_base
            │   ├── concurrency
            │   ├── data_structures
            │   ├── graphics
            │   ├── sdl_application
            │   ├── tick
            │   ├── time
            │   └── utility
            └── test/
                ├── gis
                └── infra