#include <iostream>
using namespace std;

int main() {
    int x = 4;
    
    // x'i r ismi ile `pass-by-reference` mekanizmasi ile geciriyoruz
    // ayrica x olarak da yeniden isimlendiriyoruz
    auto lambda = [&rX = x, x = x + 1]()->int {
        rX += 2;       // rX = 6
        return x + 2;  // 5 + 2, buradaki x, yeni isimlendirdigimiz
    };
    // 7, 6 basilir
    cout << lambda() << ", " << x << endl;
    
    return 0;
}

