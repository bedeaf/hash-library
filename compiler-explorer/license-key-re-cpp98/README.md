# C++98 Lisans Anahtarı Doğrulama: Tersine Mühendislik Örnekleri

Bu arşiv, lisans anahtarı doğrulama işlevlerinin derlenmiş kodda nasıl
göründüğünü incelemek amacıyla hazırlanmış yedi bağımsız C++98 örneği içerir.
Her `.cpp` dosyası tek başına derlenebilir ve Compiler Explorer'a doğrudan
aktarılabilir. Örnekler herhangi bir ticari ürünün lisans sistemini içermez.

| Dosya | Doğrulama yöntemi | Geçerli örnek girdi | Assembly'de incelenecek yapı |
| --- | --- | --- | --- |
| `01_literal.cpp` | Sabit metin karşılaştırması | `ORBIT-2026` | `strcmp` çağrısı ve koşullu dallanma |
| `02_format.cpp` | Uzunluk ve karakter biçimi | `ABCD-1234` | `strlen`, döngü ve aralık karşılaştırmaları |
| `03_check_digit.cpp` | Ağırlıklı toplam ve kontrol rakamı | `123455` | Çarpma, toplama ve `% 10` işlemi |
| `04_xor.cpp` | XOR ile gizlenmiş sabit | `ORBIT` | XOR ve bayt karşılaştırmaları |
| `05_name_serial.cpp` | Kullanıcı adına bağlı seri numarası | `bob 2180` | Bayt toplamı ve aritmetik işlemler |
| `06_fnv1a.cpp` | Kullanıcı adının FNV-1a özeti | `abc 1A47E90B` | XOR ve `16777619` ile çarpma |
| `07_toy_signature.cpp` | Küçük sayılarla imza doğrulama modeli | `42 3065` | Modüler üs alma ve `% 3233` işlemi |

## Compiler Explorer'da kullanım

1. İncelenecek dosyanın tamamı kaynak kodu alanına yapıştırılır.
2. Dil olarak C++ seçilir ve aşağıdaki seviyeye uygun derleyici seçenekleri
   **Compiler options** alanına yazılır.
3. Assembly çıktısında `valid` işlevi bulunur; geçerli ve geçersiz girdilerin
   izlediği dallar karşılaştırılır.
4. Komut satırı argümanlarıyla çalıştırma için Compiler Explorer'da
   **Execute only** görünümü açılır. Tablodaki girdiler bu görünümün argüman
   alanına yazılır. `05` ve `07` numaralı örnekler iki ayrı argüman gerektirir.

Örnekler artan zorluk sırasına göre düzenlenmiştir.

## Compiler options for all levels

Aşağıdaki seçenekler GCC ve Clang için hazırlanmıştır. Her seviyede önce
**İlk derleme**, ardından **Karşılaştırma** sütunundaki seçenekler uygulanır.
Böylece aynı kaynak kodun farklı optimizasyon düzeylerindeki assembly çıktısı
karşılaştırılabilir.

| Seviye | Dosyalar | İlk derleme | Karşılaştırma | İnceleme hedefi |
| --- | --- | --- | --- | --- |
| Başlangıç | `01`–`03` | `-std=c++98 -O0 -g` | `-std=c++98 -O1 -g` | Koşulların, döngülerin ve aritmetiğin assembly karşılığını belirlemek. |
| Orta | `04`–`05` | `-std=c++98 -O0 -g` | `-std=c++98 -O2 -g -fno-inline` | XOR, toplama ve karşılaştırma zincirindeki değişiklikleri incelemek. |
| İleri | `06`–`07` | `-std=c++98 -O2 -g -fno-inline` | `-std=c++98 -O2 -g` | İşlev içeri alma ve döngü dönüşümlerinin etkisini karşılaştırmak. |

Ek karşılaştırma için her dosya `-std=c++98 -O3` ve `-std=c++98 -Os`
seçenekleriyle de derlenebilir. İlki daha yüksek hız optimizasyonu, ikincisi
daha küçük kod boyutu hedefler. Kısa örneklerde `-O2` ile `-O3` aynı çıktıyı
üretebilir. C++98 uyumluluğunu ve derleyici uyarılarını denetlemek için
`-std=c++98 -pedantic-errors -Wall -Wextra` kullanılabilir.

## Binary Ninja için gerçekçi derleme ayarları

Compiler Explorer'ın varsayılan assembly görünümü kaynak kod ile üretilen
komutları karşılaştırmak içindir. Binary Ninja'da decompiler çıktısını
incelemek için **bağlanmış çalıştırılabilir dosya** oluşturulur. Aşağıdaki
komutlar x86-64 Linux üzerinde GCC ile ELF dosyası üretir. `-pie` ve `-s`
bağlama aşamasında etkili olduğundan yalnızca assembly çıktısına bakılarak
bu seçeneklerin sonucu değerlendirilemez.

| Profil | Derleme komutu | Binary Ninja'da beklenen fark |
| --- | --- | --- |
| Öğrenme | `g++ -std=c++98 -O0 -g -fno-inline -fno-omit-frame-pointer -fno-pie -no-pie 03_check_digit.cpp -o 03_debug` | Hata ayıklama bilgisi ve işlev adları incelemeyi kolaylaştırır. |
| Ara geçiş | `g++ -std=c++98 -O2 -g0 -fno-inline -fPIE -pie 05_name_serial.cpp -o 05_optimized` | Optimizasyon ve PIE görülür; semboller korunur. |
| Dağıtım benzeri | `g++ -std=c++98 -O2 -g0 -fPIE -pie -s 07_toy_signature.cpp -o 07_release` | Hata ayıklama bilgisi ve yerel semboller bulunmaz; işlevler içeri alınmış olabilir. |

`-g` hata ayıklama bilgisi ekler; `-g0` eklenmesini kapatır. `-s`, bağlanan
ELF dosyasındaki yerel sembol tablosunu kaldırır; dinamik kütüphane adları
görünmeye devam edebilir. Bazı sistemlerde `-g0` kullanılmasına rağmen
başlangıç nesnelerinden gelen hata ayıklama bölümleri dosyada kalabilir.
`-fPIE -pie` konumdan bağımsız
çalıştırılabilir dosya üretir. `-fno-pie -no-pie` ise ilk incelemede sabit
adresli bir dosya sağlar. `-fno-inline` işlev içeri alma optimizasyonunu
sınırlar; bu seçeneğin kaldırılması, decompiler'da işlev sınırlarının nasıl
değiştiğini karşılaştırmak için yararlıdır. `-fno-omit-frame-pointer`, ilk
profilde yığın çerçevesinin izlenmesini kolaylaştırır.

Compiler Explorer'da karşılaştırma yapılırken aynı **x86-64 GCC sürümü**
seçilmeli ve **Intel sözdizimi** kullanılmalıdır. Binary Ninja'da önce
**Disassembly** ve **Graph**, ardından **HLIL** veya **Pseudo C** görünümü
incelenebilir. Özellikle son profilde `valid` adının bulunması beklenmemelidir:
sembol kaldırma veya işlev içeri alma nedeniyle denetim mantığı başka bir
işlevin içinde görünebilir. Bu durumda `VALID` ve `INVALID` metinlerinden
başlayıp bunların kod başvuruları izlenebilir.

Bu profiller Linux ELF içindir. Windows PE dosyası incelenecekse aynı hedef
mimari için Windows derleyicisi ve farklı bağlayıcı seçenekleri gerekir.

**Eski GCC ABI karşılaştırması:** `-std=c++98` dil sürümünü belirler; modern
GCC'nin `std::__cxx11` adlarını kullanmasını tek başına engellemez.
`05_name_serial.cpp` dosyasını sembolleri koruyan ara profilde ayrıca
`-D_GLIBCXX_USE_CXX11_ABI=0` ile derlemek, eski `std::string` ABI'sinin
sembol adlarını karşılaştırmaya yarar. Bu seçenek eski bir GCC sürümünü
tam olarak taklit etmez.

Kaynaklar: [Compiler Explorer kullanım kılavuzu](https://github.com/compiler-explorer/compiler-explorer/blob/main/docs/WhatIsCompilerExplorer.md),
[GCC bağlayıcı seçenekleri](https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html),
[GCC hata ayıklama seçenekleri](https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html),
[GCC libstdc++ çift ABI açıklaması](https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dual_abi.html),
[Binary Ninja HLIL ve Pseudo C kılavuzu](https://docs.binary.ninja/guide/index.html#high-level-il).

## Yerel doğrulama

`python3 test_archive.py` komutu, her örneği
`g++ -std=c++98 -pedantic-errors -Wall -Wextra` seçenekleriyle derler ve
bir geçerli, bir geçersiz girdiyi sınar. `06_fnv1a.cpp` dosyası 32 bitlik
`unsigned int` gerektirir; bu koşul derleme sırasında kontrol edilir.

## Güvenlik kapsamı

`01`–`06` numaralı dosyalar yerel lisans kontrolü kalıplarını gösterir.
Biçim denetimi, kontrol rakamı, XOR ve FNV-1a gizli anahtarlı kimlik
doğrulaması sağlamaz. `07_toy_signature.cpp`, açık anahtarlı imza
doğrulamasının matematiksel fikrini küçük sayılarla gösterir; güvenli bir
RSA uygulaması değildir. Gerçek bir lisans sisteminde standart bir imza
şeması ve güvenilir bir kriptografi kütüphanesi kullanılmalıdır.
