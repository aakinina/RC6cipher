#ifndef RC6_HPP
#define RC6_HPP

#include "wrapper.hpp"

mp rotl(mp x, mp y);

void key_schedule(mp K, int b);

void encryption(mp pt, mp ct);

void decryption(mp ct, mp pt);

#endif
