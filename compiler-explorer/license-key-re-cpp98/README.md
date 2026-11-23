# C++98 Lisans Anahtarı Doğrulama: Tersine Mühendislik Örnekleri

Bu arşiv, lisans anahtarı doğrulama işlevlerinin derlenmiş kodda nasıl
göründüğünü incelemek amacıyla hazırlanmış 20 bağımsız C++98 örneği içerir.

| Dosya | Doğrulama yöntemi | Geçerli örnek girdi | Assembly'de incelenecek yapı |
| --- | --- | --- | --- |
| `01_literal.cpp` | Sabit metin karşılaştırması | `ORBIT-2026` | `strcmp` çağrısı ve koşullu dallanma |
| `02_format.cpp` | Uzunluk ve karakter biçimi | `ABCD-1234` | `strlen`, döngü ve aralık karşılaştırmaları |
| `03_check_digit.cpp` | Ağırlıklı toplam ve kontrol rakamı | `123455` | Çarpma, toplama ve `% 10` işlemi |
| `04_xor.cpp` | XOR ile gizlenmiş sabit | `ORBIT` | XOR ve bayt karşılaştırmaları |
| `05_name_serial.cpp` | Kullanıcı adına bağlı seri numarası | `bob 2180` | Bayt toplamı ve aritmetik işlemler |
| `06_fnv1a.cpp` | Kullanıcı adının FNV-1a özeti | `abc 1A47E90B` | XOR ve `16777619` ile çarpma |
| `07_toy_signature.cpp` | Küçük sayılarla imza doğrulama modeli | `42 3065` | Modüler üs alma ve `% 3233` işlemi |
| `08_casefold.cpp` | Harf büyüklüğünü normalleştirme | `orbit-2026` | ASCII dönüştürme ve karakter karşılaştırması |
| `09_segments.cpp` | Ön ek, gövde ve son ek denetimi | `LIC-ORBIT-END` | Birden çok `strncmp`/`strcmp` çağrısı |
| `10_poly_hash.cpp` | Kullanıcı adından polinom özet | `bob 97717` | Döngüde `31` ile çarpma |
| `11_mirrored_digits.cpp` | Simetrik rakam koşulları | `123456` | İki uçtan karakter okuma |
| `12_base36.cpp` | Taban-36 çözümleme | `1Z 71` | Harf/rakam dalları ve `36` ile çarpma |
| `13_lookup_table.cpp` | Dönüştürme tablosu | `ABCD` | Dizinden tablo okuma |
| `14_crc16.cpp` | CRC-16 kontrol değeri | `ORBIT 2326` | `0x1021` sabiti ve bit döngüsü |
| `15_machine_binding.cpp` | Makine kimliğine bağlı seri | `bob PC42 9684` | İki girdinin özetlerinin birleştirilmesi |
| `16_expiry.cpp` | Bitiş tarihi karşılaştırması | `20270101 20261123` | Biçim kontrolü ve sıralı karşılaştırma |
| `17_feature_flags.cpp` | Özellik bitleri | `A5` | `AND` işlemi ve bit maskesi |
| `18_group_relation.cpp` | Anahtar grupları arası ilişki | `1234-8649` | Ondalık çözümleme ve aritmetik koşul |
| `19_rotating_xor.cpp` | Döndürmeli XOR özeti | `bob E7` | 8 bitlik durum güncellemesi |
| `20_tea_token.cpp` | TEA benzeri tur dönüşümü | `ORBIT 7E9C999771CA4174` | `0x9E3779B9` sabiti ve tur döngüsü |

## Compiler Explorer'da kullanım

1. İncelenecek dosyanın tamamı kaynak kodu alanına yapıştırılır.
2. Dil olarak C++ seçilir ve aşağıdaki seviyeye uygun derleyici seçenekleri
   **Compiler options** alanına yazılır.
3. Assembly çıktısında `valid` işlevi bulunur; geçerli ve geçersiz girdilerin
   izlediği dallar karşılaştırılır.
4. Komut satırı argümanlarıyla çalıştırma için Compiler Explorer'da
   **Execute only** görünümü açılır. Tablodaki girdiler bu görünümün argüman
   alanına yazılır. Tablodaki boşluklar ayrı komut satırı argümanlarını
   gösterir; `15` numaralı örnek üç argüman gerektirir.

Dosya numaraları çalışma sırası önerisidir. Zorluk dağılımı aşağıda ayrıca
verilmiştir; `07` numaralı imza örneği ileri düzeydedir.

## Compiler options for all levels

Aşağıdaki seçenekler GCC ve Clang için hazırlanmıştır. Her seviyede önce
**İlk derleme**, ardından **Karşılaştırma** sütunundaki seçenekler uygulanır.
Böylece aynı kaynak kodun farklı optimizasyon düzeylerindeki assembly çıktısı
karşılaştırılabilir.

| Seviye | Dosyalar | İlk derleme | Karşılaştırma | İnceleme hedefi |
| --- | --- | --- | --- | --- |
| Başlangıç | `01`–`04`, `08`–`09`, `11`, `16`–`18` | `-std=c++98 -O0 -g` | `-std=c++98 -O1 -g` | Koşulların, döngülerin ve aritmetiğin assembly karşılığını belirlemek. |
| Orta | `05`–`06`, `10`, `12`–`15`, `19` | `-std=c++98 -O0 -g` | `-std=c++98 -O2 -g -fno-inline` | Döngü, tablo ve özet hesaplamalarının dönüşümünü incelemek. |
| İleri | `07`, `20` | `-std=c++98 -O2 -g -fno-inline` | `-std=c++98 -O2 -g` | Tur hesapları ile işlev içeri almanın etkisini karşılaştırmak. |

Ek karşılaştırma için her dosya `-std=c++98 -O3` ve `-std=c++98 -Os`
seçenekleriyle de derlenebilir. İlki daha yüksek hız optimizasyonu, ikincisi
daha küçük kod boyutu hedefler. Kısa örneklerde `-O2` ile `-O3` aynı çıktıyı
üretebilir. C++98 uyumluluğunu ve derleyici uyarılarını denetlemek için
`-std=c++98 -pedantic-errors -Wall -Wextra` kullanılabilir.

## Compiler Explorer yeterli olmadığında

Arşivdeki `Makefile`, tüm örnekleri yerel olarak üç ayrı ELF profiline derler.
Kaynak dosyalar tek başına kullanılabildiğinden yalnızca bir dosya da doğrudan
`g++` ile derlenebilir.

```sh
make -j4 all
make check
./build/release/14_crc16 ORBIT 2326
```

Derlenen dosyalar `build/debug/`, `build/optimized/` ve `build/release/`
klasörlerine yazılır. Örneğin `build/release/14_crc16` doğrudan Binary Ninja'da
açılabilir. Komut satırında `binaryninja build/release/14_crc16` kullanılabilir;
Binary Ninja başka bir konuma kurulmuşsa dosya uygulamanın içinden açılır.
`build/` klasörü GitHub arşivine eklenmez.

Yerel inceleme için `file build/release/14_crc16`,
`objdump -d -C build/optimized/14_crc16`,
`nm -C build/optimized/14_crc16` ve
`strings build/release/14_crc16` komutları da kullanılabilir. Sembolleri
kaldırılmış sürümde `nm` işlev adlarını göstermez; bu durumda Binary Ninja'da
metinler, sabitler ve bunların kod başvuruları izlenir.

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

`python3 test_archive.py` veya `make check` komutu, her örneği
`g++ -std=c++98 -pedantic-errors -Wall -Wextra` seçenekleriyle derler ve
bir geçerli, bir geçersiz girdiyi sınar. `06_fnv1a.cpp`, `10_poly_hash.cpp`
ve `20_tea_token.cpp` dosyaları 32 bitlik `unsigned int` gerektirir; bu koşul
derleme sırasında kontrol edilir.

## Güvenlik kapsamı

Örneklerin çoğu yerel lisans kontrolü kalıplarını gösterir. Biçim denetimi,
kontrol rakamı, CRC, XOR ve anahtarsız özetler kriptografik kimlik
doğrulaması sağlamaz. `07_toy_signature.cpp`, açık anahtarlı imzanın
matematiksel fikrini küçük sayılarla gösterir; güvenli bir RSA uygulaması
değildir. `20_tea_token.cpp` içinde dönüşüm anahtarı kodda bulunur ve güvenli
bir lisans imzası sağlamaz. Gerçek bir lisans sisteminde standart bir imza
şeması ve güvenilir bir kriptografi kütüphanesi kullanılmalıdır.
