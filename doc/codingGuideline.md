# uEngine4 Yazılım Geliştirme Kılavuz

Bu sayfa içerisinde, uEngine4 kapsamında yürütülecek olan yazılım geliştirme faaliyetlerinde takip edilecek standartlar, kılavuzlar ve kabuller sıralanacaktır. Bu kılavuz, temel olarak tasarım, kodlama ve birim testleri içerecektir.

uEngine4 kapsamında alınana mimari kararlar ayrıca mimari kararlar sayfasında sıralanmaktadır.

#### uEngine4 geliştirilmesinde Modern C++ (20) kullanılacaktır. Bu bağlamda kodlama kuralları da bu dile göre belirlenecektir.

## Kodlama Kılavuzu

Kodlama standardı olarak Google C++ kılavuzu takip edilecektir. Kılavuz için https://google.github.io/styleguide/cppguide.html adresine başvurulabilir.

Bunun ile birlikte https://github.com/yazilimperver/CppCoreGuidelines C++ temel kodlama kılavuzu da ilgili noktalara referans alınacaktır.

Burada, birden fazla seçenek olduğu durumda takip edilen seçenek ve olabildiğince bu kılavuzlar ile farklılaşan hususlar verilecektir.

### Başlık Dosyaları

- .inl dosyaları kullanılmayacak. Tanımlamaların hepsi başlık dosyası içerisinde yapılacaktır,
- Başlık dosyaları için #define koruması yapılacaktır, `<PROJECT>_<PATH>_<FILE>_H_`.
- Google kılavuzundan farklı olarak, forward declaration'lar kullanılabilir,
- 10 satırdan büyük ve içerisinde, koşul ya da döngü ya da başka fonksiyon çağrısı bulunan kodlar inline olarak tanımlanmamalıdır,
- Başlık dosyaları eklenirken aşağıdaki sıra gözetilmeli ve her ilgili grup arasında bir satır bırakılmalıdır
  - İlgili başlık dosyası (kaynak dosyası için),
  - Sistem başlık dosyaları,
  - C++ standart kütüphane başlık dosyaları,
  - İhtiyaç duyulan diğer başlık dosyaları.

### Kapsam (Scoping)

- namespace'ler global kapsamı anlamlı gruplara ayırmak için kullanılabilir,

- namespace'lerin bittiği yerde yorum olarak isim verilmelidir

  - ```c++
    namespace outer {
    inline namespace inner {
      void foo();
    }  // namespace inner
    }  // namespace outer
    ```

- İlgili kaynak dosya dışında kullanılmayacak tanımlamalar static olarak ya da isimsiz namespace içerisinde tanımlanmalıdır,

- Yerel değişkenler olabildiğince kullanıldıkları yere yakın ve dar kapsamda tanımlanmalıdır,

- Global string tanımlamaları için, constexpr string_view kullanımı değerlendirilmelidir,

- 

### İsimlendirme

İsimlendirmedeki temel amacımız bütün kodlarda birbirleri ile uyumlu ve takip edilebilir yaklaşım sergilemektir. Burada isimlendirmelerde, birbirleri ile çelişkili durumlardan kaçınılacaktır. Bu sayede de, kodun okunabilirliği arttırılacaktır.

- Dosya ve dizin isimleri küçük harf ve kelimeler arasında alt çizgi ile ayrılacaktır (https://www.wikiwand.com/en/Snake_case),
- C++ dosya uzantıları için .cc yerine .cpp kullanılacaktır,
- Tip (classes, structs, type aliases, enums, and type template parameters) isimlerinde alt çizgi kullanılmayacak, her kelime büyük harf ile başlayacak,
- Sınıf isimleri, isimlerden seçilecektir,
  - Sınıf üye değişkenleri (private olanlar), "m", ile başlayacaktır ve sonrasında gelen kelimeler büyük harfle başlayıp, alt çizgisiz birleştirilecektir,
  - struct üye değişkenleri büyük harf ile "m" olmadan başlayacaktır,
- Fonksiyon isimleri, fonksiyonun ne yaptığını ifade edecek şekilde verilecektir ve olabildiğince fiil ile başlayacaktır. Fonksiyon isimleri büyük harf ile başlayacaktır,
- Global değişkenler isimlendirilirken "g" ile başlayacaktır. Kelimeler arasında "_" kullanılmayacaktır,
- Sabit değişkenler isimlendirilirken "c" ile başlayacaktır. Kelimeler arasında "_" kullanılmayacaktır,
- Statik değişkenler isimlendirilirken "s" ile başlayacaktır. Kelimeler arasında "_" kullanılmayacaktır,
- Makro tanımlamaları ise tamamen büyük harf ile ve kelimeler arasında "_" kullanılarak isimlendirilecektir,
- Namespace isimlendirmeleri tamamen küçük harf olacak ve kelimeler arasında "_" kullanılarak isimlendirilecektir,
- Enumerator'ler normal tipler gibi isimlendirilecektir. Literal isimleri büyük harf ile başlar ve kelimeler arası "_" olmadan büyük harf ile başlayacaktır.



