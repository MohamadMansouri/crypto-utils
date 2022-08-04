
#include <assert.h>
#include <gmp.h>
#include <gmpxx.h>

#include "field_secp256r1_p.hpp"




Field_secp256r1_p::Field_secp256r1_p(mpz_class v) : PrimeField<Field_secp256r1_p>(v, mpz_class("ffffffff00000001000000000000000000000000ffffffffffffffffffffffff", 16))
{
}

Field_secp256r1_p::Field_secp256r1_p()
{
    p = mpz_class("ffffffff00000001000000000000000000000000ffffffffffffffffffffffff", 16);
}