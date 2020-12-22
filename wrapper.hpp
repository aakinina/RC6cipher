#ifndef WRAP_HPP
#define WRAP_HPP
#include <iostream>
#include <tommath.h>

class mp
{

    mp_int a;

public:

    mp(const char *_a)
    {
        mp_err err;
        err = mp_init(&a);
        err = mp_read_radix(&a, _a, 16);
    }

    mp(int _a)
    {
        mp_err err;
        err = mp_init(&a);
        mp_set_l(&a, _a);
    }

    mp()
    {
        mp_err err;
        err = mp_init(&a);
    }

    mp(const mp& other)
    {
        mp_err err;
        err = mp_init_copy(&a, &other.a);
    }

    ~mp()
    {
        mp_clear(&a);
    }

    mp& operator=(const mp& other)
    {
        mp_clear(&a);
        mp_err err;
        err = mp_init_copy(&a, &other.a);
        return *this;
    }

    mp operator* (mp b)
        {
            mp c;
            mp_err err;
            err = mp_mul(&this->a, &b.a, &c.a);
            return c;
        }
    mp operator% (mp b)
    {
        mp c, d;
        mp_err err;
        err = mp_div(&this->a, &b.a, &c.a, &d.a);
        return d;
    }

    mp operator/ (mp b)
    {
        mp c, d;
        mp_err err;
        err = mp_div(&this->a, &b.a, &c.a, &d.a);
        return c;
    }

    mp operator+ (mp b)
    {
        mp c;
        mp_err err;
        err = mp_add(&this->a, &b.a, &c.a);
        return c;
    }

    mp operator- (mp b)
    {
        mp c;
        mp_err err;
        err = mp_sub(&this->a, &b.a, &c.a);
        return c;
    }

    mp operator>> (mp b)
    {
        mp c, d;
        mp_err err;
        err = mp_div_2d(&a, mp_get_i32(&b.a), &c.a, &d.a);
        return c;
    }

    mp operator<< (mp b)
    {
        mp c, d;
        mp_err err;
        err = mp_mul_2d(&a, mp_get_i32(&b.a), &c.a);
        return c;
    }

    mp operator^ (mp b)
    {
        mp c;
        mp_err err;
        err = mp_xor(&a, &b.a, &c.a);
        return c;
    }

    mp operator| (mp b)
    {
        mp c;
        mp_err err;
        err = mp_or(&a, &b.a, &c.a);
        return c;
    }

    mp operator& (mp b)
    {
        mp c;
        mp_err err;
        err = mp_and(&a, &b.a, &c.a);
        return c;
    }

    friend std::ostream& operator<< (std::ostream& out, const mp A)
    {
        mp_err err;
        err = mp_fwrite(&A.a, 16, stdout);
        out << "";
        return out;
    }

    mp mask(int b)
    {
        mp c, d;
        mp_err err;
        err = mp_div_2d(&a, b, &c.a, &d.a);
        return d;
    }

};
#endif

