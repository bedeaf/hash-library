// Kalıp 16: YYYYMMDD biçimindeki bitiş tarihi verilen tarihle karşılaştırılır.
// Takvim geçerliliği denetlenmez; örnek yalnızca karşılaştırma kalıbını gösterir.
#include <cstring>
#include <iostream>

using namespace std;

bool has_date_format(const char* date) {
    const int date_length = 8;
    if (strlen(date) != date_length) {
        return false;
    }
    for (int position = 0; position < date_length; ++position) {
        if (date[position] < '0' || date[position] > '9') {
            return false;
        }
    }
    return true;
}

bool valid(const char* expiry_date, const char* current_date) {
    if (!has_date_format(expiry_date) || !has_date_format(current_date)) {
        return false;
    }
    // YYYYMMDD biçiminde sözlük sırası tarih sırasıyla aynıdır.
    return strcmp(expiry_date, current_date) >= 0;
}

int main(int argc, char** argv) {
    const char* expiry = argc > 1 ? argv[1] : "";
    const char* today = argc > 2 ? argv[2] : "";
    cout << (valid(expiry, today) ? "VALID" : "INVALID") << '\n';
}
