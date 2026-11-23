// Kalıp 16: YYYYMMDD biçimindeki bitiş tarihi verilen tarihle karşılaştırılır.
// Takvim geçerliliği denetlenmez; örnek yalnızca karşılaştırma kalıbını gösterir.
#include <cstring>
#include <iostream>

bool date_format(const char* text) {
    if (std::strlen(text) != 8)
        return false;
    for (int i = 0; i < 8; ++i)
        if (text[i] < '0' || text[i] > '9')
            return false;
    return true;
}

bool valid(const char* expiry, const char* today) {
    return date_format(expiry) && date_format(today) &&
           std::strcmp(expiry, today) >= 0;
}

int main(int argc, char** argv) {
    const char* expiry = argc > 1 ? argv[1] : "";
    const char* today = argc > 2 ? argv[2] : "";
    std::cout << (valid(expiry, today) ? "VALID" : "INVALID") << '\n';
}
