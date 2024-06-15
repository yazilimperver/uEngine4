# uEngine4 nedir?

www.yazilimperver.com sayfasında paylaştığım konuları içeren, C++ ile görselleştirme, 2B grafik, oyun ve harita benzeri etkileşimli uygulamalar geliştirmek isteyenlere yol göstermek, ilk adım olmak ve fikir vermek için geliştirilen bir kütüphanedir.

Daha önce, OpenGL, SFML, SDL2 derken birçok C++ tabanlı görselleştirme kütüphanesini, çoklu platformlar için görsel uygulamalar geliştirmede kullandım. Hatta, benzerlerini de profesyonel hayatta geliştirdim. Şu bir gerçek ki, bu işlere yeni başlayan arkadaşlar için, bu kütüphanelerin sunulan API'lerini anlayıp, zihinlerindeki projeleri hemen hayata geçirmeleri özellikle OpenGL ve SDL kullanılması durumunda biraz vakit alabiliyor, SFML belki diğerlerinden bir tık önde olabilir. Bu kütüphane ile birlikte bu ilk eşiği kolay bir şekilde atlatıp, Godot ve benzeri üst seviye bir araç da kullanmadan ama çok da alt seviyeye inmeden ve tabi ki **C++ kullanarak** bu ve benzeri uygulamaları geliştirmenize yardımcı olmak (İleride farklı dillere de belki göz atarız).

![](https://i.imgur.com/waxVImv.png)

# Amaç

Elbette bu tarz bir projeyi hayata geçirmek için giriş kısmında belirttiğim gibi bir motivasyona ihtiyaç var. Bunun ile birlikte herkes için faydalı bir proje olabilmesi için de kapsamı ve amaçlarını net bir şekilde ortaya koymamız gerektiğini düşünüyorum. Bu sayfada olabildiğince bunlara değiniyor olacağım ama kısaca özetlemek gerekirse:
* Görsel projeler geliştirmeye hızlıca başlamak,
* 2B oyun ve benzeri basit uygulamalar için alt yapı,
* CBS tabanlı görselleştirme için alt yapı,
* Modern C++ teknolojilerinin kullanımın.

## Yol Haritası

Bu başlık altında, projede belirleyeceğimiz temel kabiliyetlerin geliştirilmesine yönelik yol haritası ortaya konulacaktır.
Burada elbette sizlerden gelen geri bildirimler de benim için önemli. İlave kabiliyetler bu bağlamda bu plana ekleniyor olabilir.

### [Genel Yapılacaklar ]
| Durum | Kalem | Öncelik |
| :---: | :--- | :---: | 
| ❌ | Github actions kabiliyetinin kazandırılması. | Yüksek | 
| ✔ | Github üzerinde Issue sayfasının kullanılırr hale getirilmesi. | Yüksek | 
| ❌ | Çoklu platform desteği sunan *plug-in* mekanizmasının kazandırılması.  | Orta | 

✔ : Gerçeklendi
🚀: Çalışmaya başlandı
❌: Henüz başlamadı

Önceliğim açıkçası CI/CD entegrasyonu kapsamında Github actions olacak. Sonrasında plug-in mekanizmasına giriyor olacağız.

### [2B Oyun/Grafik Kabiliyetleri]
Bu başlık altında temel olarak 2B oyun geliştirme için eksik olan ve geliştirmeyi planladığımız kabiliyetleri sıralıyor olacağız.

| Durum | Kalem | Öncelik |
| :---: | :--- | :---: | 
| ✔ | Asset yönetim mantığının refaktör edilmesi ve yükleyici sınıfların çeşitliliğinin arttırılması.  | Yüksek | 
| ✔ | 3. parti bileşenlerin linux ve windows için otomatik olarak çekilerek oluşturulması.  | Yüksek | 
| ✔ | Android için basit bir uygulama hazırlanması.  | Orta | 
| ✔ | Örnekler arasında kolay geçiş sağlanması.  | Orta | 
| ✔ | uEngine4 duyuru yazısı.  | Orta | 
| ✔ | Dizin yapısına ilişkin sayfa.  | Orta | 
| ✔ | 2B Platform oyunu için daha kapsamlı bir "tilemap"'in hazırlanması. | Orta | 
| ✔ | 2B Platform oyunu için basit bir animatik karakterinin örneğe eklenmesi. | Orta | 
| ❌ | Basit ses kabiliyetinin eklenmesi | Orta | 
| ✔ | IMGUI kütüphanesinin entegre edilmesine yönelik bir kabiliyet eklenmesi | Düşük | 

✔ : Gerçeklendi
🚀: Çalışmaya başlandı
❌: Henüz başlamadı

Bu bağlamda çok bir kabiliyet kalmadı aslında. Sadece ses kabiliyeti onu da inşallah en yakın zamanda kazandıracağım.

### [2B CBS Kabiliyetleri]
Bu başlık altında ise, temel 2B harita kabiliyetlerine ilişkin planlanan yol haritasını takip ediyor olacağız.

| Durum | Kalem | Öncelik |
| :---: | :--- | :---: | 
| ✔ | Katman yönetim mekanizmasının kazandırılması | Yüksek | 
| ✔ | Pager kütüphanesinin düzenlenmesi (listener, vb. hususların netleştirilmesi)  | Yüksek | 
| ✔ | Paftaları hesaplamak için ayrı bir sınıf kullanılmasına yönelik guncelleme | Düşük | 
| ✔ | Paftaları internet üzerinden indirmek için gerekli kabiliyetin geliştirilmesi | Düşük | 
| ✔ | Paftaları diskten yüklenmesi için gerekli kabiliyetin geliştirilmesi | Düşük | 
| ✔ | Paftaların görüntülenmesi için gerekli kabiliyetin geliştirilmesi | Düşük | 

✔ : Gerçeklendi
🚀: Çalışmaya başlandı
❌: Henüz başlamadı

CBS için önümüz açık :)


![](https://i.imgur.com/waxVImv.png)


## Ön Koşullar

Bu motor ile sunulan kabiliyetleri kullanabilmeniz için tek ihtiyacınız Modern C++ (20) kabiliyetlerini destekleyen bir derleyiciye sahip olmak olacaktır.
Hedefimiz çoklu platform olduğu için en azından Windows, Linux ve Android (henüz pişmedi :( ) için bu kütüphaenin kullanılabilecek halde idame etmeyi planlıyorum.

Mevcut durum aşağıda gösterilmiştir:

| İşletim Sistemi | Derleyici/Araç | Durum |
| :---: | :--- | :---: |
| Windows 11 | Visual Studio 2022 | ✔  |
| Linux | G++ 11.2 | ✔  |
| Linux | Clang 10 | ✔ |
| Android | Clang XX | 🚀 |

## Kurulum

Açıkçası en çok vakit harcadığım konulardan birisi de üçüncü parti kütüphane ve yazılım bağımlılıklarının kolay bir şekilde kurulması oldu. 
Her ne kadar basit uygulamalar için ya da tecrübeli yazılımcılar için bu bağımlılıkları kotarmak zor olmasa da, yeni başlayan insanlar için bu sıkıntı olabilmekte ve insanların hevesini kırabiliyor. Fakat, sizlerin de yakında tecrübe edeceğiniz üzere, projeleriniz çapı biraz büyümeye başladığı anda, üçüncü parti uygulama ve kütüphaneleri kullanmanız kaçınılmaz oluyor.

Önceki, çok küçük çaplı olmayan projelerimin bir çoğunu Visual Studio kullanarak geliştirip paylaştığım için bu tarz hususları da Visual Studio kullanarak çözebiliyordum. Fakat son zamanlarda, çoklu platform desteği ve CMake'i kullanmaya başlamam sebebi ile Visual Studio'ya olan bağımlılığımdan kurtulmak istedim. Bu sayede hem Windows hem de Linux/WSL için projeleri oluşturma sürecinin de daha kolay olacağını düşündüm. 

Bu proje kapsamında da aslında en önemli bağımlılık SDL kütüphaneleri oldu. Bu sebeple, ilk etapta bu kütüphanelerin kolay bir şekilde kurulabilmesi için bir takım betikler hazırladım. Her ne kadar bu kütüphaneleri "sudo apt .." ile de kurabilseniz de, daha kontrollü olması açısında ilgili sitelerden son sürümleri indirip, hazırlama yöntemi bana doğru geldi açıkçası. Şimdi, Windows ve Linux için yapılması gerekenlere bir göz atalım.

Bu arada şunu belirtmekte fayda görüyorum, aşağıdaki adımlar bir betik ile de kotarılabilir, bunun farkındayım, zaten bunları da peyder pey ekliyor olacağım. 

### Windows
Windows kurulumu için izlemeniz gereken adımları aşağıya sıralıyorum. 
Şimdi diğer adımlara geçelim.

1. Öncelikle git yüklendiğinden emin olalım, kurulu değilse kuralım ve komut satırı için PATH ortam değişkenine ekleyelim,
2. Windows için herhangi bir derleyici kurduğunuzdan emin olun. Windows için ben VS2022 kullanıyorum (msvc). Sizler de Visual Studio 2022 Community Edition'ı internetten indirip kurabilirsiniz.
3. Ninja yüklendiğinden emin olalım,
    * Her ne kadar VS2022'yi kursak da, ninja hızlı derlemek için birebir,
    * **https://github.com/ninja-build/ninja/releases**, adresinden Windows için olan son sürümü indirip, yine PATH ortam değişkenine, ninja.exe'nin bulunduğu dizini ekleyiniz,
    * Komut satırı açıp `ninja --version` yazdığınızda sürüm bilgilerini görüyorsanız, tamamdır,
4. CMake yüklendiğinen emin olalım, kurulu değilse kuralım ve PATH ortam değişkenine ekleyelim,
5. Repoyu indirelim. Ayrıca submodule olarak eklenmiş repoları da almak için git submodule'leri de indirtelim
    * `git clone https://github.com/yazilimperver/uEngine4.git`
    * `git submodule update --init --recursive` ile diger repolari da alalim,
    * Daha önce indirdiyseniz `git submodule update --recursive --remote` ile güncelleyebilirsiniz.
**ÖNEMLİ NOT: Bundan sonraki adımları *install_for_windows.bat* komutu ile de uygulayabilirsiniz ;)**
6. Glew'u kuralım
    * cd code/ext
    * `curl.exe -L --ssl-revoke-best-effort https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip --output glew.zip` ile glew'i indirelim,
    * `tar -xf glew.zip`
7. SDL Kütüphanelerinin kurulması
    * cd code/ext
    * mkdir sdl2
    * cd code/ext/sdl2
    * `curl.exe -L --ssl-revoke-best-effort  https://github.com/libsdl-org/SDL/releases/download/release-2.30.2/SDL2-devel-2.30.2-VC.zip --output SDL2-devel-2.30.2-VC.zip` 
    * tar -xvf SDL2-devel-2.30.2-VC.zip
8. SDL Image Kütüphanelerinin kurulması
    * cd code/ext/sdl2
    * `curl.exe -L --ssl-revoke-best-effort https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip --output SDL2_image-devel-2.8.2-VC.zip`
    * tar -xvf SDL2_image-devel-2.8.2-VC.zip
9. Freetype kütüphanesinin kurulması
    * cd code/ext
    * `curl.exe -L --ssl-revoke-best-effort "https://github.com/ubawurinna/freetype-windows-binaries/archive/refs/tags/v2.13.2.zip" --output ft2132.zip`
    * tar -xvf ft2132.zip
    * cd freetype-windows-binaries-2.13.2
    * mkdir lib
    * `cp ".\release static\vs2015-2022\win64\freetype.lib" .\lib\`
10. SDL TTF Kütüphanelerinin kurulması
    * cd code/ext/sdl2
    * `curl.exe -L --ssl-revoke-best-effort https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.22.0-VC.zip --output SDL2_ttf-devel-2.22.0-VC.zip`
    * tar -xvf SDL2_ttf-devel-2.22.0-VC.zip
11. Curl Kütüphanelerinin kurulması
    * cd code/ext
    * `curl.exe -L --ssl-revoke-best-effort https://curl.se/download/curl-8.7.1.zip --output curl-8.7.1.zip`
    * tar -xvf curl-8.7.1.zip
    * cd curl-8.7.1
    * "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
    * cmake -B build_ninja -G "Ninja Multi-Config"
    * cmake --build build_ninja --config Release
    * cmake --build build_ninja --config Debug 
    * copy .\build_ninja\lib\Release\libcurl_imp.lib .\lib\libcurl.lib
    * copy .\build_ninja\lib\Debug\libcurl-d_imp.lib .\lib\libcurld.lib
12. Bu aşamada artık aşağıdaki komutları çağırarak, Visual Studio 2022 projesini oluşturabilirsiniz
    * cd code
    * .\scripts\buildVs.bat
    * Sonrasında .\code\build\debug-msvc\uengine4.sln dosyasını VS2022 ile açıp projeyi göz atabilir ya da oluşturabilirsiniz
13. Ninja ile oluşturmak için ise
    * cd code
    * "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
    * .\scripts\buildNinja.bat

### Linux

Linux kurulumu için izlenecek adımlar aşağıda sıralanmıştır:
1. Öncelikle git yüklendiğinden emin olalım, kurulu değilse kuralım,
    * `sudo apt install git`
2. Ninja yüklendiğinen emin olalım, kurulu değilse kuralım,
    * `sudo apt install ninja`
3. Derleme araclarini kuralim
    * `sudo apt install build-essential`
4. CMake yüklendiğinen emin olalım, kurulu değilse kuralım,
    * `sudo apt-get install cmake`
5. Repoyu indirelim. Ayrıca submodule olarak eklenmiş repoları da almak için git submodule'leri de indirtelim
    * `git clone https://github.com/yazilimperver/uEngine4.git`
    * `git submodule update --init --recursive` ile diger repolari da alalim,
    * Daha önce indirdiyseniz `git submodule update --recursive --remote` ile güncelleyebilirsiniz.
6. OpenGL kutuphanelerini kuralim
   1. `sudo apt-get install libxmu-dev libxi-dev libgl-dev -y`
7. Glew'u kuralim
   * `sudo apt-get install libglew-dev`
8. SDL Kütüphanelerinin kurulması
    * cd code/ext
    * mkdir sdl2
    * cd sdl2
    * `wget https://github.com/libsdl-org/SDL/releases/download/release-2.30.2/SDL2-2.30.2.tar.gz` 
    * tar -xvf SDL2-2.30.2.tar.gz
    * cd SDL2-2.30.2
    * cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    * cmake --build build --config Release --parallel
    * sudo cmake --install build --config Release
9. SDL Image Kütüphanelerinin kurulması
    * cd code/ext/sdl2
    * wget https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-2.8.2.tar.gz
    * tar -xvf SDL2_image-2.8.2.tar.gz
    * cd SDL2_image-2.8.2
    * cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    * cmake --build build --config Release --parallel
    * sudo cmake --install build --config Release
10. SDL TTF Kütüphanelerinin kurulması
    * sudo apt-get install libfreetype-dev
    * sudo apt-get install libjpeg-dev
    * cd code/ext/sdl2
    * `wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.22.0.tar.gz` 
    * tar -xvf SDL2_ttf-2.22.0.tar.gz
    * cd SDL2_ttf-2.22.0
    * cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    * cmake --build build --config Release --parallel
    * sudo cmake --install build --config Release
11. DevIL kütüphanelerinin kurulması
    * cd code/ext
    * wget https://github.com/DentonW/DevIL/archive/refs/tags/v1.8.0.tar.gz
    * tar -xvf v1.8.0.tar.gz
    * cd DevIL-1.8.0/DevIL
    * cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    * cmake --build build --config Release --parallel
    * sudo cmake --install build --config Release
12. curl kütüphanesini kuralım
    * sudo apt install libcurl4-openssl-dev

## Visual Studio Projesi

Son yapılan CMake güncellemesi ile birlikte ayrı olarak idame ettiğim VS2022 projesini artık çıkarıyorum.

## Örnekler
İnşallah zamanla daha fazla örnek olacak ama şu an için aşağıdaki örnekler bulunmakta. 

### ** SDL Example **
Bu örneğe ilişkin dosyalar "apps/sdl_example" altında bulunmakta:
* **[Simple Graphic App]** - SDL2 penceresi ve temel çizimlerin gösterilmesi
* **[Input Sample]** - SdlApplication sınıfı üzerinden klavye girdilerinin ve benzeri olay dinleyicilerinin nasıl kullanılacağına yönelik bir örnek
* **[Texture Sample]** - SDL2 doku mekanizmasının kullanılmasına yönelilk bir örnek
* **[Painter Sample]** - QTPainter benzeri, basit ve kullanışlı çizimleri gerçekleştirmenize olanak sağlayacak olan basic_engine::Painter sınıfının marifetlerinin sergilendiği örnek. Bu örneğe özellikle bakmanızı tavsiye ederim. Bir çok çizim ihtiyacınızı gidereceğiniz düşünüyorum
* **[Sprite Sample]** - Sprite sınıfının kullanımına ilişkin bir örnek
* **[Tile Map Sample]** - Tiled uygulamasının .json uzantılı çıktılarının görselleştirilmesi için kullanılabilecek TileMap sınıflarının kullanımına yönelik yine kapsamlı bir örnek
* **[Spritesheet Sample]** - Animatik gösterimler yapabilmenize olanak sağlayacak olan basic_engine::SpriteSheet sınıfına ilişkin örnek

### ** GL Example **
Bu örneğe ilişkin dosyalar "apps/gl_example" dizini altında bulunmaktadır. Bu proje ile temelde BasicGLPainter sınıfının kabiliyetleri gösterilmektedir. 
Bu örnek içerisinde SDL Example'da bulunan kabiliyetlerin tamamen OpenGL kullanılarak nasıl yapılabileceği gösterilmiştir.

Bu örneklerin aslında her bir bir ya da bir kaç yazılık içerik barındırmakta ama pek acelemiz yok açıkçası. Sayfamdaki yazılar ile bu örnekleri de detaylı irdeliyor olacağız.

## Kodlama Standardı

uEngine4 için izlenen kodlama standardına [buradan](https://github.com/yazilimperver/uEngine4/blob/main/doc/codingGuideline.md) ulaşabilirsiniz. Google C++ kodlama standardı referans alınmaktadır.

## Kullanılan Araç ve Kütüphaneler

* [SDL2, SDL2 Image, SDL2 TTF](https://https://www.libsdl.org/) - Çoklu platform desteği bulunan alt seviye girdi/çıktı, grafik, ses ve benzeri donanımlara yönelik soyutlama sunan kütüphaneler.
* [Curl](https://curl.se/libcurl/) - Birçok protokol (FTP, HTTP, vs) üzerinden veri transferi için kullanılabilecek, çok platform destekleyen kütüphanedir.
* [CMake](https://cmake.org/) - Açık kaynaklı, çoklu platformlar için yazılım oluşturma, test ve paketleme alt yapısı sunan araçtır.
* [Tiled](https://www.mapeditor.org/) - Tiled ücretsiz ve açık kaynak kodlu, kullanımı kolay ve esnek bir oyun seviye düzenleyici aracıdır.
* [Cereal](https://uscilab.github.io/cereal/) - C++ 11 uyumlu JSON, XML ve "binary" formatta serileştirme olanağı sunan tek başlıktan oluşan bir kütüphanedir.
* [DevIL](https://openil.sourceforge.net/) - Çoklu platform desteği sunan ve OpenGL/Windows GDI, SDL ve benzeri görselleştirme kütüphanelerini destekleyen, resim dosyası okuma, kaydetme ve dönüştürme kabiliyetleri sunan bir kütüphanedir.
* [FMT](https://fmt.dev/latest/index.html) - Açık kaynaklı formatlama kütüphanesi (C++ 20 ile birlikte sunulacak olan std::format'ı C++ 11 ile sunar).
* [Freetype](https://freetype.org/) - Çoklu platform için sunulan font/metin görselleştirme kütüphanesi.
* [GLEW](https://glew.sourceforge.net/) - OpenGL "extension"'larını tespit etmek için kullanılan, tak başlık dosyasından oluşan, çok platform destekli C++ kütüphanesidir.
* [GLM](https://github.com/g-truc/glm) - Başlık dosyalarından oluşan ve GLSL (OpenGL shading language) kurallarına uyan matematik kütüphanesidir.
* [GoogleTest](https://github.com/google/googletest) - Google tarafından geliştirilen birim test kütüphanesidir
* [IMGUI](https://github.com/ocornut/imgui) - Bir çok görselleştirme kütüphanesi ile kullanılabilen, basit kullanıcı arayüzü kütüphanesidir.
* [JSON](https://github.com/nlohmann/json) - Modern C++ kabiliyetlerini destekleyen JSON kütüphanesi.
* [STBImage](https://github.com/nothings/stb/blob/master/stb_image.h) - Tek başlık dosyasından oluşan ve resim yüklemek için kullanılabilecek dosya.

## Nasıl Katkı Sağlarım?

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

TODO

## Sürüm

Kütüphanenin sürüm takibi için [SemVer](http://semver.org/) yaklaşımı kullanılacaktır. Yayınlanan sürümler için [tags on this repository](https://github.com/your/project/tags) takip edilebilir.

TODO

## Yazarlar

* **Yazılımperver** 

Projeye katkıda bulunanların listesi için [katkıda bulunanlar](https://github.com/your/project/contributors) sayfasına göz atabiliriz.

## Lisans

Bu projenin lisanslaması için [LICENSE.md](LICENSE.md) dosyasına bakılabilir.
