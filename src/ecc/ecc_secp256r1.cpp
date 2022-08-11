#include <assert.h>
#include <string.h>
#include <gmp.h>
#include <gmpxx.h>

#include "ecc_secp256r1.hpp"

namespace ecc
{

Curve_secp256r1::Curve_secp256r1(void)
{
    prime.set_str("ffffffff00000001000000000000000000000000ffffffffffffffffffffffff", 16);
    a.set_str("ffffffff00000001000000000000000000000000fffffffffffffffffffffffc", 16);
    b.set_str("5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b", 16);

    mpz_class Gx, Gy;
    Gx.set_str("6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296", 16);
    Gy.set_str("4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5", 16);
    G = Point_secp256r1(Gx, Gy, this); 

    order.set_str("ffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551", 16);
    cofactor.set_str("1", 16);
}

Curve_secp256r1::~Curve_secp256r1(void)
{

}

}
