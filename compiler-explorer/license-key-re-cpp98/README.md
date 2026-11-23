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
4. Program çalıştırılacaksa tabloda yer alan girdi komut satırı argümanı
   olarak verilir. `05` ve `07` numaralı örnekler iki ayrı argüman gerektirir.

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
