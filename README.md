# uEngine4

www.yazilimperver.com sayfamda yazmış olduğum ve paylaştığım konuları içeren, C++ ile basit grafik, oyun ve dahi harita uygulaması geliştirmek isteyenlere yol göstermek, ilk adım olmak ve fikir vermek için geliştirdiğim bir kütüphanedir. Tabi ki Unreal Engine'i andırdığı doğrudur (isim olarak 😊), fakat pek alakası yoktur. Tamamen amatör bir ruhla yazılmakla birlikte belirli bir standart ve kuralları da barındırması hedeflenmektedir.

Neyse üçüncü dili bırakalım da mevzuya girelim :) OpenGL, SFML, SDL2 derken birçok C++ tabanlı görselleştirme kütüphanesini, çoklu platformlar için görsel uygulamalar geliştirmede kullandım. Hatta, benzerlerini de profesyonel hayatta geliştirdim. Şu bir gerçek ki, bu işlere yeni başlayan arkadaşlar için, bu kütüphanelerin sunulan API'lerini anlayıp, zihinlerindeki projeleri hemen hayata geçirmeleri özellikle OpenGL ve SDL kullanılması durumunda biraz vakit alabiliyor, SFML belki diğerlerinden bir tık önde olabilir. Bu kütüphane ile birlikte bu ilk eşiği kolay bir şekilde atlatıp, Godot ve benzeri üst seviye bir araç da kullanmadan ama çok da alt seviyeye inmeden ve tabi ki **C++ kullanarak** bu ve benzeri uygulamaları geliştirmenize yardımcı olmak.

![](https://i.imgur.com/waxVImv.png)

# Amaç

Elbette bu tarz bir projeyi hayata geçirmek için giriş kısmında belirttiğim gibi bir motivasyona ihtiyaç var. Bunun ile birlikte takipçiler ve kullanıcılar için faydalı bir proje olabilmesi için de kapsamı ve amaçlarını net bir şekilde ortaya koymamız gerektiğini düşünüyorum. Bu başlık içerisinde, bunları kısa bir şekilde sıralıyor olacağım. 

## Yol Haritası

Bu başlık altında, projede belirleyeceğimiz temel kabiliyetlerin geliştirilmesine yönelik yol haritası ortaya konulacaktır.
Burada elbette sizlerden gelen geri bildirimler de benim için önemli. İlave kabiliyetler bu bağlamda bu plana ekleniyor olabilir.

### [2B Oyun/Grafik Kabiliyetleri]
Bu başlık altında temel olarak 2B oyun geliştirme için eksik olan ve geliştirmeyi planladığımız kabiliyetleri sıralıyor olacağız.

| Durum | Kalem | Öncelik |
| :---: | :--- | :---: | 
| ❌ | **3. parti bileşenlerin linux kütüphanelerinin oluşturulması. ** | Yüksek | 
| ❌ | **Android için örnek bir uygulama hazırlanması. ** | Yüksek | 
| ❌ | **2B Platform oyunu için uzun bir platform "tilemap"'in hazırlanması.** | Orta | 
| ❌ | **2B Platform oyunu için basit bir animatik karakterinin örneğe eklenmesi.** | Orta | 
| ❌ | **Basit ses kabiliyetinin eklenmesi** | Orta | 
| ❌  | **IMGUI kütüphanesinin entegre edilmesine yönelik bir kabiliyet eklenmesi** | Düşük | 

✔ : Gerçeklendi
🚀: Çalışmaya başlandı
❌: Henüz başlamadı

### [2B CBS Kabiliyetleri]
Bu başlık altında ise, temel 2B harita kabiliyetlerine ilişkin planlanan yol haritasını takip ediyor olacağız.

| Durum | Kalem | Öncelik |
| :---: | :--- | :---: | 
| ❌ | **[Pager kütüphanesinin düzenlenmesi (listener, vb. hususların netleştirilmesi)] ** | Yüksek | 
| ❌ | **[Paftaları hesaplamak için ayrı bir sınıf kullanılmasına yönelik guncelleme]** | Düşük | 
| ❌ | **[Paftaları internet üzerinden indirmek için gerekli kabiliyetin geliştirilmesi]** | Düşük | 
| ❌ | **[Paftaları diskten yüklenmesi için gerekli kabiliyetin geliştirilmesi]** | Düşük | 
| ❌ | **[Paftaların görüntülenmesi için gerekli kabiliyetin geliştirilmesi]** | Düşük | 

✔ : Gerçeklendi
🚀: Çalışmaya başlandı
❌: Henüz başlamadı

![](https://i.imgur.com/waxVImv.png)


## Ön Koşullar

Bu motor ile sunulan kabiliyetleri kullanabilmeniz için tek ihtiyacınız Modern C++ (20) kabiliyetlerini destekleyen bir derleyiciye sahip olmak olacaktır.
Hedefimiz çoklu platform olduğu için en azından Windows, Linux ve Android için bu kütüphaenin kullanılabilecek halde idame etmeyi planlıyorum.

Mevcut durum aşağıda gösterilmiştir:

| İşletim Sistemi | Derleyici/Araç | Durum |
| :---: | :--- | :---: |
| Windows 11 | Visual Studio 2022 | ✔  |
| Linux | G++ XX | ❌ |
| Android | Clang XX | 🚀 |

## Kurulum

Açıkçası en çok vakit harcadığım konulardan birisi de üçüncü parti kütüphane ve yazılım bağımlılıklarının kolay bir şekilde kurulması oldu. 
Her ne kadar basit uygulamalar için ya da tecrübeli yazılımcılar için bu bağımlılıkları kotarmak zor olmasa da, yeni başlayan insanlar için bu sıkıntı olabilmekte ve insanların hevesini kırabiliyor. 

Önceki, çok küçük çaplı olmayan projelerimin bir çoğunu Visual Studio kullanarak geliştirip paylaştığım için bu tarz hususları da VS kullanarak çözebiliyordum. Fakat son zamanlarda, çoklu platform desteği ve CMake kullanımı ile birlikte, farklı yollar aramaya başladım. Elbette, bu noktada ilk adım CMake bağımlılıklarını kullanmak oldu. Windows için ilgili kütüphaneleri indirip, CMake üzerinden Visual Studio Projesi kolayca oluşturup, projeleri derlerken, WSL2 ve Linux için, bu kadar kolay olmadı açıkçası. 

Bu proje kapsamında da aslında en önemli bağımlılık SDL kütüphaneleri oldu. Bu sebeple, ilk etapta bu kütüphanelerin kolay bir şekilde kurulabilmesi için bir takım betikler hazırladım. Her ne kadar bu kütüphaneleri "sudo apt .." ile de kurabilseniz de, daha kontrollü olması açısında ilgili sitelerden son sürümleri indirip, hazırlama yöntemi bana doğru geldi açıkçası. Şimdi, Windows ve Linux için yapılması gerekenlere bir göz atalım:

### Windows

Windows için /code/src dizini altındaki "prepareSDLAndProjectForWin.bat", SDL kütüphanelerinin indirilmesi, CMake ile Vs2022'ye yönelik dosyaların hazırlanması için gerekli adımları içermektedir. Vs2022'den farklı bir geliştirme ortamı için ilgili betiğin içeriğini güncelleyebilirsiniz.

SDL'in farklı sürümlerini kullanabilmek için ise yine /code/src/ext/sdl2_libraries dizini altında bulunan "PrepareSDL2ForWindows.bat" betiğini düzenleyebilirsiniz.

Windows için bu betik, SDL2 ve Glew kütüphanelerini indirmektedir.

### Linux

Linux için de benzer bir şekilde /code/src dizini altındaki "PrepareSDL2ForLinux.sh" betiği, SDL kütüphaneleri ve diğer üçüncü parti bağımlılıkların indirilmesi, bunların derlenmesi, kurulması ve son olarak da uygulamanın, Ninja aracı ile oluşturulmasına yönelik gerekli dosyaları oluşturmasından sorumludur.


Bu benim Linux'e çok aşina olmadığımdan da olabilir elbette. Bu sebeple, olabildiğince kurulum adımlarını otomatize etmeyi hedefledim.


## Visual Studio Projesi

## Kodlama Standardı

uEngine4 için izlenen kodlama standardına [buradan](https://github.com/yazilimperver/uEngine4/blob/main/doc/codingGuideline.md) ulaşabilirsiniz. Google C++ kodlama standardı referans alınmaktadır.

## Kullanılan Araç ve Kütüphaneler

* [CMake](https://cmake.org/) - Açık kaynaklı, çoklu platformlar için yazılım oluşturma, test ve paketleme alt yapısı sunan araçtır.
* [Tiled](https://www.mapeditor.org/) - Tiled ücretsiz ve açık kaynak kodlu, kullanımı kolay ve esnek bir oyun seviye düzenleyici aracıdır.
* [Cereal](https://uscilab.github.io/cereal/) - C++ 11 uyumlu JSON, XML ve "binary" formatta serileştirme olanağı sunan tek başlıktan oluşan bir kütüphanedir.


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
