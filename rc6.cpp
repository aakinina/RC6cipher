#include "rc6.hpp"

mp w = 32;
int r = 20;
int bytes = 4;
int c = (16 + bytes - 1) / bytes;
mp lgw = 5;
mp P32 = "B7E15163";
mp Q32 = "9E3779B9";

mp* S = new mp[2 * r + 4];


mp rotl(mp x, mp y)
{
    return (((x) << (y & (w - mp(1)))) | ((x) >> (w - (y & (w - 1)))));
}

void key_schedule(mp K, int b)
{
    int i, j, s, v;
    mp* L = new mp[(32 + bytes - 1) / bytes];
    mp A, B;

    L[c - 1] = 0;
    for (i = b - 1; i >= 0; --i)
        L[i / bytes] = (L[i / bytes] << 8) + (K >> i).mask(1);

    S[0] = P32;
    for (i = 1; i <= 2 * r + 3; ++i)
        S[i] = (S[i - 1] + Q32);

    A = B = i = j = 0;
    v = 2 * r + 4;
    if (c > v)
        v = c;
    v *= 3;

    for (s = 1; s <= v; ++s)
    {
        A = S[i] = rotl(S[i] + A + B, mp(3));
        B = L[j] = rotl(L[j] + A + B, A + B);
        i = (i + 1) % (2 * r + 4);
        j = (j + 1) % c;
    }
}

void encryption(mp pt, mp ct)
{
    mp A, B, C, D, t, u, x;

    A = pt >> 24;
    B = (pt >> 16).mask(8);
    C = (pt >> 8).mask(8);
    D = pt.mask(8);
    B = B + S[0];
    D = D + S[1];

    for (int i = 0; i <= r; ++i)
    {
        t = rotl(B * (mp(2) * B + mp(1)), lgw);
        u = rotl(D * (mp(2) * D + mp(1)), lgw);
        A = rotl(A ^ t, u) + S[i];
        C = rotl(C ^ u, t) + S[i + 1];

        x = A;
        A = B;
        B = C;
        C = D;
        D = x;

    }

    A = A + S[2 * r + 2];
    C = A + S[2 * r + 3];
    ct = ((A << 24) | (B << 16) | (C << 8) | D);
}

#include "rc6.hpp"

void decryption(mp ct, mp pt)
{
    mp A, B, C, D, t, u, x;

    A = pt >> 24;
    B = (pt >> 16).mask(8);
    C = (pt >> 8).mask(8);
    D = pt.mask(8);
    C = C - S[2 * r + 3];
    A = A - S[2 * r + 2];

    for (int i = r; i >= 0; --i)
    {
        x = D;
        D = C;
        C = B;
        B = A;
        A = x;
        u = rotl(D * (mp(2) * D + mp(1)), lgw);
        t = rotl(B * (mp(2) * B + mp(1)), lgw);
        C = rotl(C - S[i + 1], mp(32) - t) ^ u;
        A = rotl(A - S[i], mp(32) - u) ^ t;
    }
    D = D - S[1];
    B = B - S[0];
    pt = ((A << 24) | (B << 16) | (C << 8) | D);
}
