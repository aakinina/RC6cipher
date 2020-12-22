#include <iostream>

#include "rc6.hpp"

int main()
{
    mp k1 = "00000000000000000000000000000000";
    key_schedule(k1,32);
    mp pt1 = "00000000000000000000000000000000";
    mp ct1;
    encryption(pt1, ct1);
    std::cout << "Key: " << k1 << "\n";
    std::cout << "Ciphertext: " << ct1 << "\n";
    decryption(ct1, pt1);
    std::cout << "Plaintext: " << pt1 << "\n\n";

    mp k2 = "02132435465768798a9bacbdcedfe0f1";
    key_schedule(k2,32);
    mp pt2 = "0123456789abcdef0112233445566778";
    mp ct2;
    encryption(pt2, ct2);
    std::cout << "Ciphertext: " << ct2 << "\n";
    decryption(ct2, pt2);
    std::cout << "Plaintext: " << pt2;

    return 0;
}
