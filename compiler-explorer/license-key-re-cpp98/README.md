# C++98 lisans anahtari kontrolu: RE alistirma arsivi

Bu arsiv, Compiler Explorer'da kaynak kodu assembly ile yan yana incelemek
icin yedi bagimsiz, tek dosyali ornek icerir. Her `.cpp` dosyasi tek basina
derlenir. Ornekler herhangi bir ticari urunun lisans algoritmasini taklit etmez.

| Dosya | Kontrol kalibi | Ornek girdi | Assembly'de izle |
| --- | --- | --- | --- |
| `01_literal.cpp` | Sabit metin karsilastirmasi | `ORBIT-2026` | `strcmp`, kosullu dal |
| `02_format.cpp` | Uzunluk, tire, harf/rakam | `ABCD-1234` | `strlen`, dongu, aralik karsilastirmalari |
| `03_check_digit.cpp` | Agirlikli toplam ve kontrol rakami | `123455` | carpma, toplama, `% 10` |
| `04_xor.cpp` | XOR ile gizlenmis sabit | `ORBIT` | XOR ve bayt karsilastirmasi |
| `05_name_serial.cpp` | Kullanici adindan seri sayisi | `bob 2180` | bayt toplami ve aritmetik |
| `06_fnv1a.cpp` | Kullanici adinin FNV-1a ozeti | `abc 1A47E90B` | XOR ve `16777619` ile carpma |
| `07_toy_signature.cpp` | Kucuk sayilarla imza dogrulama modeli | `42 3065` | modular us alma, `% 3233` |

## Compiler Explorer

1. Bir dosyanin tamamini kaynak editorune yapistir.
2. Dil olarak C++ ve derleyici secenekleri olarak once `-std=c++98 -O0` kullan.
3. `valid` fonksiyonunu assembly'de bul; basarili ve basarisiz yolu izle.
4. Sonra `-std=c++98 -O2` ile tekrar derle ve optimizasyonun neyi
   degistirdigine bak.
5. Programi calistirmak icin tabloda verilen girdiyi komut satiri argumanlari
   olarak kullan. `05` ve `07` iki ayri arguman ister.

Ornekler zorluk sirasindadir. Ilk dort dosya baslamak icin yeterlidir.

## Yerel dogrulama

`python3 test_archive.py` her ornegi `g++ -std=c++98 -pedantic-errors -Wall
-Wextra` ile derler ve bir gecerli, bir gecersiz girdiyi dener. Derleyici
yalnizca C++98 dil ozelliklerini kabul eder. `06` icin 32 bit `unsigned int`
gerekir; kod bunu derleme asamasinda kontrol eder.

## Guvenlik siniri

`01`–`06` yerel lisans kontrolu kaliplaridir. Format, kontrol rakami, XOR ve
FNV-1a gizli anahtarli kimlik dogrulamasi saglamaz. `07`, acik anahtarla imza
dogrulamanin matematik fikrini gosterir; sayilari cok kucuktur ve guvenli
RSA imzasi degildir. Gercek lisans sistemi icin standart imza semasi ve
guvenilir bir kriptografi kutuphanesi gerekir.
